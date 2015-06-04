#ifndef UTILS_TIMERMANAGER_HPP_
#define UTILS_TIMERMANAGER_HPP_

#include "Ogre.h"
// Template on this class to get the template requirement out of the way
// in cases where you don't want to use member function callbacks.
class _Empty {
};

// template this class on the class containing your timer callbacks ..
// that is, if you want to use member function callbacks.
/**
 * @brief
 * @details
 *
 * Usage:
 * // declare your timer handler
 * bool timerHandler( int Timer_ID);
 *
 * // declare the TimerManager
 * TimerManager<_Empty> mTimer;
 *
 * // add some timers (this can be done at any time)
 * mTimer.AddTimer(500, timerHandler,9,true,true);
 * mTimer.AddTimer(240, timerHandler,3,true,true);
 *
 * // add Timer as a frame listener so it gets updates
 * mApp->GetRoot()->addFrameListener(&mTimer);
 *
 * @date 2015-04-28
 * @author Benjamin Ellenberger
 */
template<typename callbackClass>
class TimerManager: public Ogre::FrameListener {
public:
	// UseFrameStarted true will cause timer callbacks to be sent
	// during frame started.  False: callbacks will be sent
	// during frame ended.
	TimerManager(bool _UseFrameStarted = true) :
			mUseFrameStarted(_UseFrameStarted) {
	}

	// Two choices of callbacks.
	// You can template this class on your class
	// and use it to call member functions
	// if your handler returns false, the timer will NOT be repeated.
	typedef bool (callbackClass::*MemberTimerHandler)(int);
	// or you can provide a pointer to a static or global function
	typedef bool (*TimerCallback)(int mTimerID);

	// AddTimer() adds a timer to be called back after a given period
	// Timer_ID is an optional identifier for later removal
	// Repeat is a boolean flag, if true the timer handler will be called
	// every Period untill stopped.  if false, timer handler will be called only once.
	// Play_Catchup is a boolean flag, if true the timer handler will be called multiple times
	// if TimerManager is unable to call at the requested rate due to low frame rate.
	// the only difference between these two add functions is one uses member function callback
	// the other uses a global callback.
	void addTimer(unsigned long Period, TimerCallback callback, int Timer_ID =
			-1, bool Repeat = false, bool Play_Catchup = true) {
		TimerInstance t;
		t.mMemberTimerHandler = NULL;
		t.mcallbackClass = NULL;
		t.mTimerCallback = callback;
		t.mPeriod = Period;
		t.mTimerID = Timer_ID;
		t.mRepeat = Repeat;
		t.mPlayCatchup = Play_Catchup;
		unsigned long now = mTimer.getMilliseconds();
		mTimers.insert(std::make_pair(now + Period, t));
	}

	void addTimer(unsigned long period, MemberTimerHandler callback,
			callbackClass* callbackObject, int timerID = -1, bool repeat =
					false, bool playCatchup = true) {
		TimerInstance t;
		t.mMemberTimerHandler = callback;
		t.mcallbackClass = callbackObject;
		t.mTimerCallback = NULL;
		t.mPeriod = period;
		t.mTimerID = timerID;
		t.mRepeat = repeat;
		t.mPlayCatchup = playCatchup;
		unsigned long now = mTimer.getMilliseconds();
		mTimers.insert(std::make_pair(now + period, t));
	}

	// searches for and removes all timers with given timer_ID
	// note: If all the timers have the same ID, and that ID is prided here, it will end ALL timers
	void stopTimer(int timerID) {
		typename TimerMap::iterator i;
		for (i = mTimers.begin(); i != mTimers.end(); ++i) {
			if (i->second.timerID == timerID) {
				i = mTimers.erase(i);
			}
		}
	}
protected:
	// Ogre::Timer to watch time pass by.
	Ogre::Timer mTimer;

	// definition of our timer instance.
	class TimerInstance {
	public:
		MemberTimerHandler mMemberTimerHandler;
		callbackClass* mcallbackClass;
		TimerCallback mTimerCallback;
		unsigned long mPeriod;
		int mTimerID;
		bool mRepeat;
		bool mPlayCatchup;

		unsigned long trigger(unsigned long behind) {
			bool callback_return = false;
			long temp_behind = (long) behind;
			while (temp_behind >= 0) {
				temp_behind -= mPeriod;
				callback_return = callback();
				if (!mRepeat) {
					return 0;
				}
				if (!callback_return) {
					return 0;
				}
				if (mPeriod == 0) {
					return 0;
				}
				if (!mPlayCatchup) {
					continue;
				}
			}

			return (mPeriod - (behind % mPeriod));
		}

		bool callback() {
			if ((mMemberTimerHandler != NULL) && (mcallbackClass != NULL)) {
				return (mcallbackClass->*mMemberTimerHandler)(mTimerID);
			} else if (mTimerCallback != NULL) {
				return mTimerCallback(mTimerID);
			}
			return false;
		}
	};
	// inherited frameStarted and frame Ended from Ogre::FrameListener
	virtual bool frameStarted(const Ogre::FrameEvent& evt) {
		if (!mUseFrameStarted)
			return true;
		while (next())
			;
		return true;
	}

	virtual bool frameEnded(const Ogre::FrameEvent& evt) {
		if (mUseFrameStarted)
			return true;
		while (next())
			;
		return true;
	}

	// process next timer (if applicable)
	bool next() {
		if (mTimers.empty())
		{
			return false;
		}
		unsigned long now = mTimer.getMilliseconds();
		unsigned long then = mTimers.begin()->first;
		//std::cout << " now >= then " << now << " >= " << then << std::endl;
		if (now >= then) {
			TimerInstance currentTimer = mTimers.begin()->second; // get a copy of the timer instance
			mTimers.erase(mTimers.begin()); // pop the sucker off the map.
			unsigned long next_trigger = currentTimer.trigger(now - then); // trigger it

			if (next_trigger > 0) {
				// if it returns non-zero, put it back in the map.
				mTimers.insert(
						std::make_pair(now + next_trigger, currentTimer));
			}
			return true;
		}
		return false;
	}

	// container for all our timer instances.
	typedef std::multimap<int, TimerInstance> TimerMap;
	TimerMap mTimers;

	// determines if callbacks happen durring frame started, or frame ended.
	bool mUseFrameStarted;
};

#endif /* UTILS_TIMERMANAGER_HPP_ */
