#ifndef MODEL_UNIVERSE_EVOLUTION_EVOLUTIONMODEL_HPP_
#define MODEL_UNIVERSE_EVOLUTION_EVOLUTIONMODEL_HPP_

//# corresponding headers
//# forward declarations
//# system headers
#include <vector>

//## controller headers
//## model headers
#include <boost/serialization/vector.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/version.hpp>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
#include <model/universe/evolution/Reaper.hpp>
#include <model/universe/evolution/population/PopulationModel.hpp>

//## view headers
//## utils headers

/**
 * @brief		The model of the evolution holds information about the evolution.
 * @details		Details
 * @date		2015-03-08
 * @author		Benjamin Ellenberger
 */
class EvolutionModel {
public:

	/**
	 *  Evolution phase
	 */
	enum EvolutionPhase {
		VARIATION_PHASE, //!< Phase in which the genomes are varied
		EVALUATION_PHASE, //!< Phase in which the phenotypes are evaluated
		PROCESSING_PHASE, //!< Phase in which the phenotype's scores are processed
		CULLING_PHASE, //!< Phase in which the bad phenotypes are culled
		NUM_EVOLUTION_PHASES //!< NUM_EVOLUTION_PHASES
	};

	/**
	 * The type evaluation
	 */
	enum EvaluationType {
		INDIVIDUAL_EVALUATION, //!< Every individual gets separately evaluated.
		N_INDIVIDUALS_TOURNAMENT_EVALUATION, //!< Individual get evaluated in groups of n (Individuals Tournament).
		POPULATION_EVALUATION, //!< Each population gets evaluated as a whole.
		N_POPULATION_EVALUATION, //!< A group of n individuals from each population get evaluated.
		N_POPULATIONS_TOURNAMENT_EVALUATION, //!< N populations are evaluated together (Populations Tournament).
		POPULATIONS_EVALUATION, //!< All populations are evaluated together.
		NUM_EVALUATION_TYPES
	};

	EvolutionModel(const EvaluationType type,
		const double evaluationTime, const int tournamentSize);
	EvolutionModel();
	~EvolutionModel();

	/**
	 * Initialize the evolution model.
	 */
	void initialize();

	/**
	 * Perform embryogenesis on all creatures that are not developed.
	 */
	void performEmbryogenesis();

	/**
	 * Add a new population to the evolution model.
	 * @param populationModel The population to be added.
	 */
	void addNewPopulation(PopulationModel* const populationModel);

	/**
	 * Proceed the evaluation.
	 * @return If the evaluation could be proceeded.
	 */
	bool proceedEvaluation();

	/**
	 * Evaluate the evolution.
	 * @return If the evolution could be evaluated.
	 */
	bool evaluate();

	/**
	 * Process the evaluated individuals.
	 * @return If the individuals could be processed.
	 */
	bool process();

	/**
	 * Cull the bad individuals.
	 * @return If the individuals could be culled.
	 */
	bool cull();

	/**
	 * Variate the individuals.
	 * @return If the individuals could be variated.
	 */
	bool variate();

	//Accessor methods
	Reaper& getReaper() {
		return mReaper;
	}

	const EvolutionPhase getPhase() const {
		return mPhase;
	}

	const EvaluationType getType() const {
		return mType;
	}

	std::vector<PopulationModel*>& getPopulationModels() {
		return mPopulationModels;
	}

	const double getEvaluationTime() const {
		return mEvaluationTime;
	}

	const std::vector<CreatureModel*>::size_type getCurrentCreatureIndex() const {
		return mCurrentCreatureIndex;
	}

	bool setCurrentCreatureIndex(
		const std::vector<CreatureModel*>::size_type currentCreatureIndex);

	const std::vector<PopulationModel*>::size_type getCurrentPopulationIndex() const {
		return mCurrentPopulationIndex;
	}

	void setCurrentPopulationIndex(
		const std::vector<PopulationModel*>::size_type currentPopulationIndex) {
		mCurrentPopulationIndex = currentPopulationIndex;
	}

	const unsigned long getTournamentSize() const {
		return mTournamentSize;
	}

	//Serialization

	/**
	 * Give access to boost serialization
	 */
	friend class boost::serialization::access;

	/**
	 * Serializes the evolution model to a string.
	 * @param os The ostream.
	 * @param evolution The evolution we want to serialize.
	 * @return A string containing all information about the evolution.
	 */
	friend std::ostream & operator<<(std::ostream &os,
		const EvolutionModel &evolution) {
		os

		<< "/EvolutionModel: EvaluationType=" << evolution.mType /**!< The evaluation type */

		<< "\n/TournamentSize=" << evolution.mTournamentSize /**!< The tournament size */

		<< "\n/EvaluationTime=" << evolution.mEvaluationTime /**!< The evaluation time */
		<< "\n/Phase=" << evolution.mPhase; /**!< The phase the evolution is currently in */

		/**The populations of the planet*/
		for (std::vector<PopulationModel*>::const_iterator it =
			evolution.mPopulationModels.begin();
			it != evolution.mPopulationModels.end(); it++) {
			os << (**it);
			os << "||";
		}

		/** The current population*/
		os << "\n/Current Epoch=" << evolution.mCurrentPopulationIndex
		/** The current creature*/
		<< "\n/Current Creature=" << evolution.mCurrentCreatureIndex;
		return os;
	}

	/**
	 * Serializes the evolution to an xml file.
	 * @param ar The archive.
	 * @param The file version.
	 */
	template<class Archive>
	void serialize(Archive & ar, const unsigned int /* file_version */) {
		ar
		/**!< The evaluation type */
		& BOOST_SERIALIZATION_NVP(mType)

		/**!< The tournament size */
		& BOOST_SERIALIZATION_NVP(mTournamentSize)

		/**!< The evaluation time */
		& BOOST_SERIALIZATION_NVP(mEvaluationTime)

		/**!< The phase the evolution is currently in */
		& BOOST_SERIALIZATION_NVP(mPhase)

		/**The populations of the planet*/
		& BOOST_SERIALIZATION_NVP(mPopulationModels)

		/** The current population*/
		& BOOST_SERIALIZATION_NVP(mCurrentPopulationIndex)

		/** The current creature*/
		& BOOST_SERIALIZATION_NVP(mCurrentCreatureIndex);
	}

private:
	std::vector<PopulationModel*> mPopulationModels; /**!< The vector of populations that are evaluated. */

	std::vector<PopulationModel*>::size_type mCurrentPopulationIndex; /**!< The currently evaluated population. */

	std::vector<CreatureModel*>::size_type mCurrentCreatureIndex; /**!< The currently evaluated creature. */

	Reaper mReaper; /**!< The reaper of this evolution model. */

	EvolutionPhase mPhase; /**!< The phase this evolution is in. */

	EvaluationType mType; /**!< The type of evolution model. */

	double mEvaluationTime; /**!< Evaluation time */

	unsigned long mTournamentSize; /**!< Tournament size */
};
BOOST_CLASS_VERSION(EvolutionModel, 1)
#endif /* MODEL_UNIVERSE_EVOLUTION_EVOLUTIONMODEL_HPP_ */
