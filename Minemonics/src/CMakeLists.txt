#/*
#-----------------------------------------------------------------------------
#Filename:    CMakeLists.txt
#-----------------------------------------------------------------------------
#
#This source file is part of the Minemonics 3D Virtual Creature simulator
#
#-----------------------------------------------------------------------------
#*/
cmake_minimum_required(VERSION 2.6)
 
project(Minemonics)

#Set if it should be built in debug or release mode
set(CMAKE_BUILD_TYPE "Debug")
#set(CMAKE_BUILD_TYPE "Release")

#DEVELOPMENT INPUT
# Append header files here


set(MODELHDRS
	# model
	./model/Serializable.hpp
	
	# data collection model
	./model/data/DataSink.hpp
	./model/data/MathGLDataset.hpp
	
	## environment
    ./model/universe/environments/EnvironmentModel.hpp
    ./model/universe/environments/PlaneModel.hpp
	./model/universe/environments/EnvironmentPhysics.hpp
	./model/universe/environments/bullet/EnvironmentBt.hpp
	./model/universe/environments/bullet/HillsBt.hpp
	./model/universe/environments/bullet/PlaneBt.hpp
	
    ## bullet physics controller
    ./model/universe/environments/physics/PhysicsController.hpp
    ./model/universe/environments/physics/GroundController.hpp
    ./model/universe/environments/physics/BulletPicker.hpp
	
	## juries
	./model/universe/evolution/juries/Jury.hpp
	./model/universe/evolution/juries/AverageVelocity.hpp
	./model/universe/evolution/juries/IntegralAverageVelocity.hpp
	./model/universe/evolution/juries/AverageHeight.hpp
	./model/universe/evolution/juries/GroundContactRatio.hpp
	./model/universe/evolution/juries/GroundContactQty.hpp
	
	## universe
	./model/universe/EvaluationModel.hpp
	./model/universe/UniverseModel.hpp
	./model/universe/PlanetModel.hpp
	./model/universe/Epoch.hpp
	./model/universe/CollisionHandler.hpp
	
	## evolution
	./model/universe/evolution/EvolutionModel.hpp
	./model/universe/evolution/Reaper.hpp
	./model/universe/evolution/CreatureFitnessComparator.hpp
	./model/universe/evolution/CreatureFitnessScoreComparator.hpp
	./model/universe/evolution/population/PopulationModel.hpp
	./model/universe/evolution/population/creature/CreatureModel.hpp
	
	## model organism builders
	./model/universe/evolution/population/creature/modelOrganism/ragdoll/RagDollBuilder.hpp
	./model/universe/evolution/population/creature/modelOrganism/snake/SnakeBuilder.hpp
	./model/universe/evolution/population/creature/modelOrganism/modelLeg/ModelLegBuilder.hpp
	./model/universe/evolution/population/creature/modelOrganism/pod/PodBuilder.hpp
	
	## genome
	./model/universe/evolution/population/creature/genome/Genome.hpp
	./model/universe/evolution/population/creature/genome/DirectGenome.hpp
	./model/universe/evolution/population/creature/genome/IndirectGenome.hpp
	./model/universe/evolution/population/creature/genome/MixedGenome.hpp
	./model/universe/evolution/population/creature/genome/genetics/Embryogenesis.hpp
	./model/universe/evolution/population/creature/genome/genetics/BaseGenerator.hpp
	./model/universe/evolution/population/creature/genome/genetics/PhenotypeGenerator.hpp
	./model/universe/evolution/population/creature/genome/Gene.hpp
	./model/universe/evolution/population/creature/genome/GeneBranch.hpp
	./model/universe/evolution/population/creature/genome/morphology/Morphogene.hpp
    ./model/universe/evolution/population/creature/genome/morphology/MorphogeneBranch.hpp
    ./model/universe/evolution/population/creature/genome/controller/ControllerGene.hpp
    ./model/universe/evolution/population/creature/genome/controller/ChaoticControllerGene.hpp
	./model/universe/evolution/population/creature/genome/controller/SineControllerGene.hpp
	
	## phenome
	./model/universe/evolution/population/creature/phenome/PhenomeModel.hpp
	./model/universe/evolution/population/creature/phenome/SRBPhenomeModel.hpp
	./model/universe/evolution/population/creature/phenome/ComponentModel.hpp
	./model/universe/evolution/population/creature/phenome/morphology/limb/LimbModel.hpp
	./model/universe/evolution/population/creature/phenome/morphology/limb/FSLimbModel.hpp
	./model/universe/evolution/population/creature/phenome/morphology/limb/SRBLimbModel.hpp
	./model/universe/evolution/population/creature/phenome/morphology/limb/LimbPhysics.hpp
	./model/universe/evolution/population/creature/phenome/morphology/limb/FSLimbBt.hpp
	./model/universe/evolution/population/creature/phenome/morphology/limb/SRBLimbBt.hpp
	./model/universe/evolution/population/creature/phenome/morphology/joint/JointModel.hpp
	./model/universe/evolution/population/creature/phenome/morphology/joint/FSJointModel.hpp
	./model/universe/evolution/population/creature/phenome/morphology/joint/SRBJointModel.hpp
    ./model/universe/evolution/population/creature/phenome/morphology/joint/JointPhysics.hpp
    ./model/universe/evolution/population/creature/phenome/morphology/joint/FSJointBt.hpp
	./model/universe/evolution/population/creature/phenome/morphology/joint/SRBJointBt.hpp
	./model/universe/evolution/population/creature/phenome/morphology/effector/motor/Motor.hpp
	./model/universe/evolution/population/creature/phenome/morphology/effector/motor/ServoMotor.hpp
	./model/universe/evolution/population/creature/phenome/morphology/effector/motor/FSServoMotor.hpp
	./model/universe/evolution/population/creature/phenome/morphology/effector/motor/SRBServoMotor.hpp
	
	## sensors
	./model/universe/evolution/population/creature/phenome/morphology/sensor/Sensor.hpp
	./model/universe/evolution/population/creature/phenome/morphology/sensor/exteroceptor/Tactioceptor.hpp
	./model/universe/evolution/population/creature/phenome/morphology/sensor/proprioceptor/Proprioceptor.hpp
	./model/universe/evolution/population/creature/phenome/morphology/sensor/proprioceptor/JointProprioceptor.hpp
	./model/universe/evolution/population/creature/phenome/morphology/sensor/proprioceptor/JointAngleceptor.hpp
	./model/universe/evolution/population/creature/phenome/morphology/sensor/proprioceptor/JointVelocityceptor.hpp
	./model/universe/evolution/population/creature/phenome/morphology/sensor/proprioceptor/JointForceceptor.hpp
	./model/universe/evolution/population/creature/phenome/morphology/sensor/proprioceptor/JointLimitceptor.hpp
		
	## creature controller
	./model/universe/evolution/population/creature/phenome/controller/Controller.hpp
	./model/universe/evolution/population/creature/phenome/controller/ControlInput.hpp
	./model/universe/evolution/population/creature/phenome/controller/ControlOutput.hpp
	./model/universe/evolution/population/creature/phenome/controller/sine/SineController.hpp
	./model/universe/evolution/population/creature/phenome/controller/chaotic/ChaoticController.hpp
)
set(MODELSRCS
    # model
    ./model/Serializable.cpp
    
    # data collection model
	./model/data/DataSink.cpp
	./model/data/MathGLDataset.cpp
    
    ## environment
    ./model/universe/environments/EnvironmentModel.cpp
    ./model/universe/environments/PlaneModel.cpp
    ./model/universe/environments/EnvironmentPhysics.cpp
	./model/universe/environments/bullet/EnvironmentBt.cpp
	./model/universe/environments/bullet/HillsBt.cpp
	./model/universe/environments/bullet/PlaneBt.cpp
	
	## bullet physics controller
	./model/universe/environments/physics/PhysicsController.cpp
	./model/universe/environments/physics/GroundController.cpp
	./model/universe/environments/physics/BulletPicker.cpp
   
    ## juries
	./model/universe/evolution/juries/Jury.cpp
	./model/universe/evolution/juries/AverageVelocity.cpp
	./model/universe/evolution/juries/IntegralAverageVelocity.cpp
	./model/universe/evolution/juries/AverageHeight.cpp
	./model/universe/evolution/juries/GroundContactRatio.cpp
    ./model/universe/evolution/juries/GroundContactQty.cpp
	
	## universe
	./model/universe/EvaluationModel.cpp
	./model/universe/UniverseModel.cpp
	./model/universe/PlanetModel.cpp
	./model/universe/Epoch.cpp
	
	## evolution
	./model/universe/evolution/EvolutionModel.cpp
	./model/universe/evolution/Reaper.cpp
	./model/universe/evolution/CreatureFitnessComparator.cpp
	./model/universe/evolution/CreatureFitnessScoreComparator.cpp
	./model/universe/evolution/population/PopulationModel.cpp
	./model/universe/evolution/population/creature/CreatureModel.cpp
	
	## model organism builders
	./model/universe/evolution/population/creature/modelOrganism/ragdoll/RagDollBuilder.cpp
	./model/universe/evolution/population/creature/modelOrganism/snake/SnakeBuilder.cpp
	./model/universe/evolution/population/creature/modelOrganism/modelLeg/ModelLegBuilder.cpp
	./model/universe/evolution/population/creature/modelOrganism/pod/PodBuilder.cpp
	
	## genome
	./model/universe/evolution/population/creature/genome/Genome.cpp
	./model/universe/evolution/population/creature/genome/DirectGenome.cpp
	./model/universe/evolution/population/creature/genome/IndirectGenome.cpp
	./model/universe/evolution/population/creature/genome/MixedGenome.cpp
	./model/universe/evolution/population/creature/genome/genetics/Embryogenesis.cpp
	./model/universe/evolution/population/creature/genome/genetics/BaseGenerator.cpp
	./model/universe/evolution/population/creature/genome/genetics/PhenotypeGenerator.cpp
	./model/universe/evolution/population/creature/genome/Gene.cpp
	./model/universe/evolution/population/creature/genome/GeneBranch.cpp
	./model/universe/evolution/population/creature/genome/morphology/Morphogene.cpp
	./model/universe/evolution/population/creature/genome/morphology/MorphogeneBranch.cpp
	./model/universe/evolution/population/creature/genome/controller/ControllerGene.cpp
	./model/universe/evolution/population/creature/genome/controller/ChaoticControllerGene.cpp
	./model/universe/evolution/population/creature/genome/controller/SineControllerGene.cpp
	
	## phenome
	./model/universe/evolution/population/creature/phenome/PhenomeModel.cpp
	./model/universe/evolution/population/creature/phenome/FSPhenomeModel.cpp
	./model/universe/evolution/population/creature/phenome/SRBPhenomeModel.cpp
	./model/universe/evolution/population/creature/phenome/ComponentModel.cpp
	./model/universe/evolution/population/creature/phenome/morphology/limb/LimbModel.cpp
	./model/universe/evolution/population/creature/phenome/morphology/limb/FSLimbModel.cpp
	./model/universe/evolution/population/creature/phenome/morphology/limb/SRBLimbModel.cpp
	./model/universe/evolution/population/creature/phenome/morphology/limb/LimbPhysics.cpp
	./model/universe/evolution/population/creature/phenome/morphology/limb/FSLimbBt.cpp
	./model/universe/evolution/population/creature/phenome/morphology/limb/SRBLimbBt.cpp
	./model/universe/evolution/population/creature/phenome/morphology/joint/JointModel.cpp
	./model/universe/evolution/population/creature/phenome/morphology/joint/FSJointModel.cpp
	./model/universe/evolution/population/creature/phenome/morphology/joint/SRBJointModel.cpp
    ./model/universe/evolution/population/creature/phenome/morphology/joint/JointPhysics.cpp
    ./model/universe/evolution/population/creature/phenome/morphology/joint/FSJointBt.cpp
	./model/universe/evolution/population/creature/phenome/morphology/joint/SRBJointBt.cpp
	./model/universe/evolution/population/creature/phenome/morphology/effector/motor/Motor.cpp
	./model/universe/evolution/population/creature/phenome/morphology/effector/motor/ServoMotor.cpp
	./model/universe/evolution/population/creature/phenome/morphology/effector/motor/FSServoMotor.cpp
	./model/universe/evolution/population/creature/phenome/morphology/effector/motor/SRBServoMotor.cpp
	
	## sensors
	./model/universe/evolution/population/creature/phenome/morphology/sensor/Sensor.cpp
	./model/universe/evolution/population/creature/phenome/morphology/sensor/exteroceptor/Tactioceptor.cpp
	./model/universe/evolution/population/creature/phenome/morphology/sensor/proprioceptor/Proprioceptor.cpp
	./model/universe/evolution/population/creature/phenome/morphology/sensor/proprioceptor/JointProprioceptor.cpp
	./model/universe/evolution/population/creature/phenome/morphology/sensor/proprioceptor/JointAngleceptor.cpp
	./model/universe/evolution/population/creature/phenome/morphology/sensor/proprioceptor/JointVelocityceptor.cpp
	./model/universe/evolution/population/creature/phenome/morphology/sensor/proprioceptor/JointForceceptor.cpp
	./model/universe/evolution/population/creature/phenome/morphology/sensor/proprioceptor/JointLimitceptor.cpp
	
	## creature controller
    ./model/universe/evolution/population/creature/phenome/controller/Controller.cpp
	./model/universe/evolution/population/creature/phenome/controller/ControlInput.cpp
	./model/universe/evolution/population/creature/phenome/controller/ControlOutput.cpp
	./model/universe/evolution/population/creature/phenome/controller/sine/SineController.cpp
	./model/universe/evolution/population/creature/phenome/controller/chaotic/ChaoticController.cpp
)
set(CONTROLLERHDRS
	# controller
	# input handlers
	./controller/input/ApplicationScancode.hpp
	./controller/input/ApplicationKeycode.hpp
	./controller/input/ApplicationMousecode.hpp
	./controller/input/SDL2InputHandler.hpp
	./controller/input/CEGUIInputHandler.hpp
	./controller/input/OgreInputHandler.hpp
	./controller/input/KeyboardStateInputHandler.hpp
	./controller/input/InputUtils.hpp
	
	## view controller
	./controller/viewcontroller/ViewController.hpp
	./controller/viewcontroller/camera/CameraHandler.hpp
	
	## object save controller
	./controller/SaveController.hpp
	
	## application state handler
	./controller/StateHandler.hpp
	
	## evaluation controller
	./controller/EvaluationController.hpp
	./controller/Evaluation.hpp
	
    ## universe
    ./controller/universe/Universe.hpp
    ./controller/universe/Planet.hpp
    
    # entity controllers/model-view facades to control objects at both sides
    ## environments
    ./controller/universe/environments/Environment.hpp
    ./controller/universe/environments/Plane.hpp
    
    ## evolution
    ./controller/universe/evolution/Evolution.hpp
    ./controller/universe/evolution/population/Population.hpp
	
    ## creature
    ./controller/universe/evolution/population/creature/Creature.hpp
    ./controller/universe/evolution/population/creature/phenome/Phenome.hpp
    ./controller/universe/evolution/population/creature/phenome/Component.hpp
    ./controller/universe/evolution/population/creature/phenome/morphology/Limb.hpp
    ./controller/universe/evolution/population/creature/phenome/morphology/Joint.hpp
)
set(CONTROLLERSRCS
	# controller
	## Input handlers
	./controller/input/SDL2InputHandler.cpp
	./controller/input/CEGUIInputHandler.cpp
	./controller/input/OgreInputHandler.cpp
	./controller/input/KeyboardStateInputHandler.cpp
	
	## view controller
	./controller/viewcontroller/ViewController.cpp
	./controller/viewcontroller/camera/CameraHandler.cpp
		
	## application state handler
	./controller/StateHandler.cpp
	
	## evaluation controller
	./controller/EvaluationController.cpp
	./controller/Evaluation.cpp
		
	## universe
    ./controller/universe/Universe.cpp
    ./controller/universe/Planet.cpp
    
	# entity controllers/model-view facades to control objects at both sides
	## environments
    ./controller/universe/environments/Environment.cpp
    ./controller/universe/environments/Plane.cpp
    
    ## evolution
    ./controller/universe/evolution/Evolution.cpp
    ./controller/universe/evolution/population/Population.cpp
	
    ## creature
    ./controller/universe/evolution/population/creature/Creature.cpp
    ./controller/universe/evolution/population/creature/phenome/Phenome.cpp
    ./controller/universe/evolution/population/creature/phenome/Component.cpp
    ./controller/universe/evolution/population/creature/phenome/morphology/Limb.cpp
    ./controller/universe/evolution/population/creature/phenome/morphology/Joint.cpp
)
set(VIEWHDRS
	# view
	## environments
	./view/universe/environments/EnvironmentGraphics.hpp
	./view/universe/environments/envgenerators/PerlinNoiseTerrainGenerator.hpp
	./view/universe/environments/EnvironmentO3D.hpp
	./view/universe/environments/OpenSeaO3D.hpp
	./view/universe/environments/PlaneO3D.hpp
	./view/universe/environments/HillsO3D.hpp
	
	## creature
    ./view/universe/evolution/population/creature/phenome/morphology/limb/LimbGraphics.hpp
	./view/universe/evolution/population/creature/phenome/morphology/limb/LimbO3D.hpp
	./view/universe/evolution/population/creature/phenome/morphology/joint/JointGraphics.hpp
	./view/universe/evolution/population/creature/phenome/morphology/joint/JointO3D.hpp
	
	## physics debug drawing
	./view/visualization/bulletphysics/OgreBtDebugDrawer.hpp
	
	## information overlay
	./view/visualization/overlay/InfoOverlay.hpp
	./view/visualization/overlay/InfoOverlayData.hpp
	
    ## CEGUI
	./view/visualization/CEGUI/GUISheetHandler.hpp
	./view/visualization/CEGUI/MenuBar.hpp
	./view/visualization/CEGUI/BasePanel.hpp
	./view/visualization/CEGUI/MovablePanel.hpp
	./view/visualization/CEGUI/elements/BoxSlider.hpp
    ./view/visualization/CEGUI/infopanels/ParamsPanel.hpp
	./view/visualization/CEGUI/infopanels/FPSPanel.hpp
	./view/visualization/CEGUI/infopanels/DetailsPanel.hpp
	./view/visualization/CEGUI/infopanels/graphpanels/MathGLPanel.hpp
    ./view/visualization/CEGUI/ShowCasePanel.hpp
    ./view/visualization/CEGUI/configpanels/NewPlanetPanel.hpp
    ./view/visualization/CEGUI/configpanels/NewPopulationPanel.hpp
    ./view/visualization/CEGUI/configpanels/EditPlanetPanel.hpp
    ./view/visualization/CEGUI/configpanels/EditPopulationPanel.hpp
    ./view/visualization/CEGUI/configpanels/LoadPlanetPanel.hpp
    ./view/visualization/CEGUI/configpanels/LoadPopulationPanel.hpp
    ./view/visualization/CEGUI/configpanels/FileDialog.hpp
    	
    ## Videocapture
	./view/videocapture/Ogre3DFFMPEGVideoWriter.hpp
	
	## picking
	./view/picking/MousePicker.hpp
    
    # procedural
	./view/visualization/procedural/ProceduralPlatform.h
	./view/visualization/procedural/Procedural.h
	./view/visualization/procedural/ProceduralMeshGenerator.h
	./view/visualization/procedural/ProceduralBoxGenerator.h
	./view/visualization/procedural/ProceduralCapsuleGenerator.h
	./view/visualization/procedural/ProceduralConeGenerator.h
	./view/visualization/procedural/ProceduralCylinderGenerator.h
	./view/visualization/procedural/ProceduralIcoSphereGenerator.h
	./view/visualization/procedural/ProceduralPlaneGenerator.h
	./view/visualization/procedural/ProceduralSphereGenerator.h
	./view/visualization/procedural/ProceduralRoot.h
	./view/visualization/procedural/ProceduralRoundedBoxGenerator.h
	./view/visualization/procedural/ProceduralTorusGenerator.h
	./view/visualization/procedural/ProceduralTorusKnotGenerator.h
	./view/visualization/procedural/ProceduralTubeGenerator.h
	./view/visualization/procedural/ProceduralUtils.h
	./view/visualization/procedural/ProceduralExtruder.h
	./view/visualization/procedural/ProceduralLathe.h
	./view/visualization/procedural/ProceduralShape.h
	./view/visualization/procedural/ProceduralShapeGenerators.h
	./view/visualization/procedural/ProceduralPath.h
	./view/visualization/procedural/ProceduralPathGenerators.h
	./view/visualization/procedural/ProceduralTrack.h
	./view/visualization/procedural/ProceduralSplines.h
	./view/visualization/procedural/ProceduralTriangulator.h
	./view/visualization/procedural/ProceduralTriangleBuffer.h
	./view/visualization/procedural/ProceduralStableHeaders.h
	./view/visualization/procedural/ProceduralMultiShape.h
	./view/visualization/procedural/ProceduralGeometryHelpers.h
)
set(VIEWSRCS
	# view
	## environments
	./view/universe/environments/EnvironmentGraphics.cpp
    ./view/universe/environments/envgenerators/PerlinNoiseTerrainGenerator.cpp
	./view/universe/environments/EnvironmentO3D.cpp
	./view/universe/environments/HillsO3D.cpp
	./view/universe/environments/OpenSeaO3D.cpp
	./view/universe/environments/PlaneO3D.cpp
	
	## creatures
	./view/universe/evolution/population/creature/phenome/morphology/limb/LimbGraphics.cpp
	./view/universe/evolution/population/creature/phenome/morphology/limb/LimbO3D.cpp
	./view/universe/evolution/population/creature/phenome/morphology/joint/JointGraphics.cpp
	./view/universe/evolution/population/creature/phenome/morphology/joint/JointO3D.cpp
	
	## physics debug drawing
	./view/visualization/bulletphysics/OgreBtDebugDrawer.cpp
	
	
	## information overlay
	./view/visualization/overlay/InfoOverlay.cpp
	./view/visualization/overlay/InfoOverlayData.cpp
	
	## CEGUI
	./view/visualization/CEGUI/GUISheetHandler.cpp
	./view/visualization/CEGUI/MenuBar.cpp
	./view/visualization/CEGUI/BasePanel.cpp
	./view/visualization/CEGUI/MovablePanel.cpp
	./view/visualization/CEGUI/elements/BoxSlider.cpp
	./view/visualization/CEGUI/infopanels/ParamsPanel.cpp
	./view/visualization/CEGUI/infopanels/FPSPanel.cpp
	./view/visualization/CEGUI/infopanels/DetailsPanel.cpp
	./view/visualization/CEGUI/infopanels/graphpanels/MathGLPanel.cpp
	./view/visualization/CEGUI/ShowCasePanel.cpp
	./view/visualization/CEGUI/configpanels/NewPlanetPanel.cpp
    ./view/visualization/CEGUI/configpanels/NewPopulationPanel.cpp
    ./view/visualization/CEGUI/configpanels/EditPlanetPanel.cpp
    ./view/visualization/CEGUI/configpanels/EditPopulationPanel.cpp
    ./view/visualization/CEGUI/configpanels/LoadPlanetPanel.cpp
    ./view/visualization/CEGUI/configpanels/LoadPopulationPanel.cpp
    ./view/visualization/CEGUI/configpanels/FileDialog.cpp

	## Videocapture
	./view/videocapture/Ogre3DFFMPEGVideoWriter.cpp
	
	## picking
	./view/picking/MousePicker.cpp
	
	# procedural
	./view/visualization/procedural/ProceduralBoxGenerator.cpp
	./view/visualization/procedural/ProceduralCapsuleGenerator.cpp
	./view/visualization/procedural/ProceduralConeGenerator.cpp
	./view/visualization/procedural/ProceduralCylinderGenerator.cpp
	./view/visualization/procedural/ProceduralIcoSphereGenerator.cpp
	./view/visualization/procedural/ProceduralPlaneGenerator.cpp
	./view/visualization/procedural/ProceduralRoot.cpp
	./view/visualization/procedural/ProceduralRoundedBoxGenerator.cpp
	./view/visualization/procedural/ProceduralSphereGenerator.cpp
	./view/visualization/procedural/ProceduralTorusGenerator.cpp
	./view/visualization/procedural/ProceduralTorusKnotGenerator.cpp
	./view/visualization/procedural/ProceduralTubeGenerator.cpp		
	./view/visualization/procedural/ProceduralUtils.cpp
	./view/visualization/procedural/ProceduralShape.cpp		
	./view/visualization/procedural/ProceduralShapeGenerators.cpp
	./view/visualization/procedural/ProceduralPath.cpp
	./view/visualization/procedural/ProceduralPathGenerators.cpp
	./view/visualization/procedural/ProceduralTrack.cpp
	./view/visualization/procedural/ProceduralExtruder.cpp
	./view/visualization/procedural/ProceduralLathe.cpp
	./view/visualization/procedural/ProceduralTriangulator.cpp
	./view/visualization/procedural/ProceduralPrecompiledHeaders.cpp
	./view/visualization/procedural/ProceduralMultiShape.cpp
	./view/visualization/procedural/ProceduralGeometryHelpers.cpp
)
set(MISCHDRS
	# configuration
	./configuration/ApplicationConfiguration.hpp
	./configuration/CameraConfiguration.hpp
	./configuration/ControlConfiguration.hpp
	./configuration/PhysicsConfiguration.hpp
	./configuration/MorphologyConfiguration.hpp
	./configuration/GeneticsConfiguration.hpp
	./configuration/EnvironmentConfiguration.hpp
	./configuration/EvaluationConfiguration.hpp
	./configuration/EvolutionConfiguration.hpp
	./configuration/OgreSystemConfigStrings.hpp
	./configuration/CEGUIConfiguration.hpp
	./configuration/GUIConfiguration.hpp
	./configuration/LoggerConfiguration.hpp
	./configuration/Definitions.hpp
	./configuration/SRBJointDefinitions.hpp
	./configuration/SerializationConfiguration.hpp
	./configuration/PlotConfiguration.hpp
	
	# logger
	./utils/logging/Logger.hpp
	
	# debugger
	./utils/Debugger.hpp
	
	# randomness
	./utils/Randomness.hpp
	
	# NumericUtils
	./utils/NumericUtils.hpp
	
	# name generator
	./utils/NameGenerator.hpp
	
	# StringFormatter
	./utils/StringFormatter.hpp
	
	# euler angle calculations
	./utils/ogre3D/Euler.hpp
	
	# conversion utils
    ./utils/ogre3D/OgreBulletUtils.hpp
    
    # bullet utils
    ./utils/bullet/BulletUtils.hpp
    
    # serialization
    ./utils/serialization/FilesystemManipulator.hpp
    
    # mathutils
    ./utils/MathUtils.hpp
)
set(MISCSRCS

    # configuration
	./configuration/ApplicationConfiguration.cpp
	./configuration/CameraConfiguration.cpp
	./configuration/ControlConfiguration.cpp
	./configuration/PhysicsConfiguration.cpp
	./configuration/MorphologyConfiguration.cpp
	./configuration/GeneticsConfiguration.cpp
	./configuration/EnvironmentConfiguration.cpp
	./configuration/EvaluationConfiguration.cpp
	./configuration/EvolutionConfiguration.cpp
	./configuration/CEGUIConfiguration.cpp
	./configuration/GUIConfiguration.cpp
	./configuration/LoggerConfiguration.cpp
	./configuration/SerializationConfiguration.cpp
    ./configuration/PlotConfiguration.cpp
    
	# logger
	./utils/logging/Logger.cpp
	
	# debugger
	./utils/Debugger.cpp
	
	# randomness
	./utils/Randomness.cpp
	
	# numeric utils
	./utils/NumericUtils.cpp
	
	# name generator
	./utils/NameGenerator.cpp
	
	# StringFormatter
	./utils/StringFormatter.cpp
	
	# Math Utils
    ./utils/MathUtils.cpp
)

set(TESTHDRS
    ${MODELHDRS}
    #${VIEWHDRS}
    #${CONTROLLERHDRS}
    ${MISCHDRS}
)
set(TESTSRCS
    ${MODELSRCS}
    #${VIEWSRCS}
    #${CONTROLLERSRCS}
    ${MISCSRCS}
    
    ## unit test cases
    ## (unit tests usually only test the model)
    ## therefore it should never be necessary to include the srcs from view and controller above
    
    ## universe
    ./model/universe/UniverseModel_test.cpp
    ./model/universe/PlanetModel_test.cpp
    
    ## juries
    ./model/universe/evolution/juries/AverageVelocity_test.cpp
    ./model/universe/evolution/juries/IntegralAverageVelocity_test.cpp
    ./model/universe/evolution/juries/AverageHeight_test.cpp
    ./model/universe/evolution/juries/GroundContactRatio_test.cpp
    ./model/universe/evolution/juries/GroundContactQty_test.cpp
    
    ## creatures
   ./model/universe/evolution/population/creature/CreatureModel_test.cpp
   ./model/universe/evolution/population/PopulationModel_test.cpp
    
    # genome
    ./model/universe/evolution/population/creature/genome/MixedGenome_test.cpp
    
    ## morphology
    ./model/universe/evolution/population/creature/genome/morphology/MorphogeneBranch_test.cpp
    ./model/universe/evolution/population/creature/genome/morphology/Morphogene_test.cpp
    
    ## controllers
    ./model/universe/evolution/population/creature/genome/controller/ChaoticControllerGene_test.cpp
    ./model/universe/evolution/population/creature/genome/controller/SineControllerGene_test.cpp
    
    # phenome
    ./model/universe/evolution/population/creature/phenome/PhenomeModel_test.cpp
    ./model/universe/evolution/population/creature/phenome/SRBPhenomeModel_test.cpp
    ./model/universe/evolution/population/creature/phenome/FSPhenomeModel_test.cpp
    ## controllers
    ./model/universe/evolution/population/creature/phenome/controller/sine/SineController_test.cpp
    ./model/universe/evolution/population/creature/phenome/controller/chaotic/ChaoticController_test.cpp
    
    ## morphology
    ./model/universe/evolution/population/creature/phenome/morphology/limb/SRBLimbBt_test.cpp
    ./model/universe/evolution/population/creature/phenome/morphology/limb/SRBLimbModel_test.cpp
    ./model/universe/evolution/population/creature/phenome/morphology/joint/SRBJointBt_test.cpp
    ./model/universe/evolution/population/creature/phenome/morphology/joint/SRBJointModel_test.cpp
    ./model/universe/evolution/population/creature/phenome/morphology/effector/motor/SRBServoMotor_test.cpp
    
    ./model/universe/evolution/population/creature/phenome/morphology/limb/FSLimbBt_test.cpp
    ./model/universe/evolution/population/creature/phenome/morphology/limb/FSLimbModel_test.cpp
    ./model/universe/evolution/population/creature/phenome/morphology/joint/FSJointBt_test.cpp
    ./model/universe/evolution/population/creature/phenome/morphology/joint/FSJointModel_test.cpp
    ./model/universe/evolution/population/creature/phenome/morphology/effector/motor/FSServoMotor_test.cpp
    
    # misc
    ./utils/NameGenerator_test.cpp
    ./utils/Randomness_test.cpp
    ./utils/MathUtils_test.cpp
    
    #test runner
    ./test/TestRunner.cpp
)
set(HDRS
    ${MODELHDRS}
    ${VIEWHDRS}
    ${CONTROLLERHDRS}
    ${MISCHDRS}
    
    # base
	./BaseApplication.hpp
	./SimulationManager.hpp
)

# Append source files here
set(SRCS
    ${MODELSRCS}
    ${VIEWSRCS}
    ${CONTROLLERSRCS}
    ${MISCSRCS}
    
    # base
	./BaseApplication.cpp
	./SimulationManager.cpp	
)

message(STATUS "Compiler version:${CMAKE_CXX_COMPILER_VERSION}")
 
if(WIN32)
	set(CMAKE_MODULE_PATH "$ENV{OGRE_HOME}/CMake/;${CMAKE_MODULE_PATH}")
	set(OGRE_SAMPLES_INCLUDEPATH
		$ENV{OGRE_HOME}/Samples/include
	)
endif(WIN32)
 
if(UNIX)
	if(EXISTS "/usr/local/lib/OGRE/cmake")

	  set(CMAKE_MODULE_PATH "/usr/local/lib/OGRE/cmake/;${CMAKE_MODULE_PATH}")
	  #set(OGRE_SAMPLES_INCLUDEPATH "/usr/local/share/OGRE/samples/Common/include/") # We could just *assume* that developers uses this basepath : /usr/local

	elseif(EXISTS "/usr/lib/OGRE/cmake")

	  set(CMAKE_MODULE_PATH "/usr/lib/OGRE/cmake/;${CMAKE_MODULE_PATH}")
	  #set(OGRE_SAMPLES_INCLUDEPATH "/usr/share/OGRE/samples/Common/include/") # Otherwise, this one

	else ()
	  message(SEND_ERROR "Failed to find module path.")
	endif(EXISTS "/usr/local/lib/OGRE/cmake")
	set(PROJECT_HOME .)
endif(UNIX)
 
if (CMAKE_BUILD_TYPE STREQUAL "")
  # CMake defaults to leaving CMAKE_BUILD_TYPE empty. This screws up
  # differentiation between debug and release builds.
  set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "Choose the type of build, options are: None (CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif ()
 
set(CMAKE_DEBUG_POSTFIX "_d")
 
set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/dist")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMakeModules/")


######################################################################
# OGRE, OGRE Terrain
######################################################################

 
find_package(OGRE REQUIRED)

# USERADDED for terrain usage
# Add OgreTerrain.{so,dll,etc.} to our linked libraries
#   These variables are defined in FindOGRE.cmake, mine is
#   found at /usr/local/lib/OGRE/cmake/
if (OGRE_Terrain_FOUND)
# append OgreTerrain to the end of the OGRE_LIBRARIES variable
  set(OGRE_LIBRARIES ${OGRE_LIBRARIES} ${OGRE_Terrain_LIBRARIES})  
  message(STATUS "Found OGRE_Terrain: ${OGRE_Terrain_LIBRARIES}")
else (OGRE_Terrain_FOUND)
  message(SEND_ERROR "OgreTerrain Library not found.")
endif(OGRE_Terrain_FOUND)


if (OGRE_Paging_FOUND)
# append OgrePaging to the end of the OGRE_LIBRARIES variable
  set(OGRE_LIBRARIES ${OGRE_LIBRARIES} ${OGRE_Paging_LIBRARIES})  
  message(STATUS "Found OGRE_Paging: ${OGRE_Paging_LIBRARIES}")
else (OGRE_Paging_FOUND)
  message(SEND_ERROR "OgrePaging Library not found.")
endif(OGRE_Paging_FOUND)

if (OGRE_Overlay_FOUND)
# append OgreOverlay to the end of the OGRE_LIBRARIES variable
  set(OGRE_LIBRARIES ${OGRE_LIBRARIES} ${OGRE_Overlay_LIBRARIES})  
  message(STATUS "Found OGRE_Overlay: ${OGRE_Overlay_LIBRARIES}")
else (OGRE_Overlay_FOUND)
  message(SEND_ERROR "OgreOverlay Library not found.")
endif(OGRE_Overlay_FOUND)
 
######################################################################
# BOOST
######################################################################
 
# Find Boost
if (WIN32 OR APPLE OR OGRE_STATIC)
	set(Boost_USE_STATIC_LIBS ON)
else ()
	# Statically linking boost to a dynamic Ogre build doesn't work on Linux 64bit
	set(Boost_USE_STATIC_LIBS OFF)
endif ()
if(OGRE_STATIC AND OGRE_BUILD_PLATFORM_APPLE_IOS)
        set(Boost_USE_MULTITHREADED OFF)
endif()
	
	
if (MINGW)
	# this is probably a bug in CMake: the boost find module tries to look for
	# boost libraries with name libboost_*, but CMake already prefixes library
	# search names with "lib". This is the workaround.
	set(CMAKE_FIND_LIBRARY_PREFIXES ${CMAKE_FIND_LIBRARY_PREFIXES} "")
endif ()
#include <OgreSceneManager.h>
  
set(MINEMONICS_BOOST_COMPONENTS log filesystem)
find_package(Boost COMPONENTS ${MINEMONICS_BOOST_COMPONENTS} REQUIRED)

set(OGRE_LIBRARIES ${OGRE_LIBRARIES} ${Boost_LIBRARIES})
set(OGRE_INCLUDE_DIRS ${OGRE_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})

if(Boost_FOUND)
	message(STATUS "Found Boost log: ${Boost_LIBRARIES}")
else ()
	message(SEND_ERROR "Failed to find Boost.")
endif(Boost_FOUND)

## OGRE dependencies

set(Boost_ADDITIONAL_VERSIONS "1.44" "1.44.0" "1.42" "1.42.0" "1.41.0" "1.41" "1.40.0" "1.40" "1.39.0" "1.39" "1.38.0" "1.38" "1.37.0" "1.37" )
# Components that need linking (NB does not include header-only components like bind)
## DEVELOPMENT: Minemonics needs log
set(OGRE_BOOST_COMPONENTS thread date_time)
find_package(Boost COMPONENTS ${OGRE_BOOST_COMPONENTS} REQUIRED)
if (NOT Boost_FOUND)
	# Try again with the other type of libs
	set(Boost_USE_STATIC_LIBS NOT ${Boost_USE_STATIC_LIBS})
	find_package(Boost COMPONENTS ${OGRE_BOOST_COMPONENTS} REQUIRED)
endif()
if (Boost_FOUND AND WIN32)
    if(Boost_VERSION GREATER 104700)
        set(OGRE_BOOST_COMPONENTS thread date_time regex system)
    endif(Boost_VERSION GREATER 104700)
    if(Boost_VERSION GREATER 104900)
        set(OGRE_BOOST_COMPONENTS thread date_time regex system chrono)
    endif(Boost_VERSION GREATER 104900)
    find_package(Boost COMPONENTS ${OGRE_BOOST_COMPONENTS} REQUIRED)
endif(Boost_FOUND AND WIN32)
find_package(Boost REQUIRED)

if(Boost_FOUND)
	message(STATUS "Found Boost: ${Boost_LIBRARIES}")
else ()
	message(SEND_ERROR "Failed to find Boost.")
endif(Boost_FOUND)
 
# Set up referencing of Boost
include_directories(${Boost_INCLUDE_DIRS})
add_definitions(-DBOOST_ALL_NO_LIB)
add_definitions(-DBOOST_LOG_DYN_LINK)
set(OGRE_LIBRARIES ${OGRE_LIBRARIES} ${Boost_LIBRARIES})

######################################################################
# SDL2
######################################################################

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIR})
set(OGRE_LIBRARIES ${OGRE_LIBRARIES} ${SDL2_LIBRARY})


######################################################################
# CEGUI
######################################################################

find_package(CEGUI REQUIRED)

include_directories(${CEGUI_INCLUDE_DIR})
set(OGRE_LIBRARIES ${OGRE_LIBRARIES} ${CEGUI_LIBRARIES})
include_directories(${CEGUI_OgreRenderer_INCLUDE_DIRS})
set(OGRE_LIBRARIES ${OGRE_LIBRARIES} ${CEGUI_OgreRenderer_LIBRARIES})

######################################################################
# MathGL (for graph drawing capabilities)
######################################################################

find_package(MathGL2 REQUIRED)

include_directories(${MATHGL2_INCLUDE_DIR})
set(OGRE_LIBRARIES ${OGRE_LIBRARIES} ${MATHGL2_LIBRARIES})

######################################################################
# FFmpeg (for video capabilities)
######################################################################

find_package(FFMPEG REQUIRED)

include_directories(${FFMPEG_INCLUDE_DIRS})
set(OGRE_LIBRARIES ${OGRE_LIBRARIES} ${FFMPEG_LIBRARIES} "-llzma")

######################################################################
# Boost
######################################################################
find_package(Boost REQUIRED random log thread date_time regex system chrono serialization)

include_directories(${Boost_INCLUDE_DIRS})
set(OGRE_LIBRARIES ${OGRE_LIBRARIES} ${Boost_LIBRARIES})

######################################################################
# Bullet 3 physics libary
######################################################################

find_package(Bullet REQUIRED)

include_directories(${BULLET_INCLUDE_DIRS})
set(OGRE_LIBRARIES ${OGRE_LIBRARIES} ${BULLET_LIBRARIES})
if(BULLET_FOUND)
	message(STATUS "Found Bullet: ${BULLET_LIBRARIES}")
	message(STATUS "--${BULLET_INCLUDE_DIRS}")
else ()
	message(SEND_ERROR "Failed to find Bullet.")
endif(BULLET_FOUND)


######################################################################
# COMPILATION
######################################################################

## headers and source definitions above
 
include_directories(
	${OGRE_INCLUDE_DIRS}
	${OGRE_SAMPLES_INCLUDEPATH}
	${OGRE_Terrain_INCLUDE_DIRS}
	${OGRE_Paging_INCLUDE_DIRS}
	${OGRE_Overlay_INCLUDE_DIRS}
	${PROJECT_HOME}
)

add_executable(Minemonics WIN32 ${HDRS} ${SRCS})
 
set_target_properties(Minemonics PROPERTIES DEBUG_POSTFIX _d)
######################################################################
# LINKING
######################################################################
 
target_link_libraries(Minemonics ${OGRE_LIBRARIES} ${OGRE_Overlay_LIBRARIES})
 
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/dist/bin)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/dist/media)
 
 
######################################################################
# POST COMPILATION (INSTALLATION etc.)
######################################################################

# post-build copy for win32
if(WIN32 AND NOT MINGW)
	add_custom_command( TARGET Minemonics PRE_BUILD
		COMMAND if not exist .\\dist\\bin mkdir .\\dist\\bin )
	add_custom_command( TARGET Minemonics POST_BUILD
		COMMAND copy \"$(TargetPath)\" .\\dist\\bin )
endif(WIN32 AND NOT MINGW)

if(MINGW OR UNIX)
	set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/dist/bin)
endif(MINGW OR UNIX)
 
if(WIN32)
 
	install(TARGETS Minemonics
		RUNTIME DESTINATION bin
		CONFIGURATIONS All)
 
	install(DIRECTORY ${CMAKE_SOURCE_DIR}/dist/Media
		DESTINATION ./
		CONFIGURATIONS Release RelWithDebInfo Debug
	)
 
	install(FILES ${CMAKE_SOURCE_DIR}/dist/bin/plugins.cfg
		${CMAKE_SOURCE_DIR}/dist/bin/resources.cfg
		DESTINATION bin
		CONFIGURATIONS Release RelWithDebInfo
	)
 
	install(FILES ${CMAKE_SOURCE_DIR}/dist/bin/plugins_d.cfg
		${CMAKE_SOURCE_DIR}/dist/bin/resources_d.cfg
		DESTINATION bin
		CONFIGURATIONS Debug
	)
 
        # NOTE: for the 1.7.1 sdk the OIS dll is called OIS.dll instead of libOIS.dll
        # so you'll have to change that to make it work with 1.7.1
	install(FILES ${OGRE_PLUGIN_DIR_REL}/OgreMain.dll
		${OGRE_PLUGIN_DIR_REL}/RenderSystem_Direct3D9.dll
		${OGRE_PLUGIN_DIR_REL}/RenderSystem_GL.dll
		${OGRE_PLUGIN_DIR_REL}/libOIS.dll
		DESTINATION bin
		CONFIGURATIONS Release RelWithDebInfo
	)
 
	install(FILES ${OGRE_PLUGIN_DIR_DBG}/OgreMain_d.dll
		${OGRE_PLUGIN_DIR_DBG}/RenderSystem_Direct3D9_d.dll
		${OGRE_PLUGIN_DIR_DBG}/RenderSystem_GL_d.dll
		${OGRE_PLUGIN_DIR_DBG}/libOIS_d.dll
		DESTINATION bin
		CONFIGURATIONS Debug
	)
 
   # as of sdk 1.7.2 we need to copy the boost dll's as well
   # because they're not linked statically (it worked with 1.7.1 though)
   install(FILES ${Boost_DATE_TIME_LIBRARY_RELEASE}
      ${Boost_THREAD_LIBRARY_RELEASE}
      DESTINATION bin
      CONFIGURATIONS Release RelWithDebInfo
   )
 
   install(FILES ${Boost_DATE_TIME_LIBRARY_DEBUG}
      ${Boost_THREAD_LIBRARY_DEBUG}
      DESTINATION bin
      CONFIGURATIONS Debug
   )
endif(WIN32)

if(UNIX)
 
	install(TARGETS Minemonics
		RUNTIME DESTINATION bin
		CONFIGURATIONS All)
 
	install(DIRECTORY ${CMAKE_SOURCE_DIR}/dist/media
		DESTINATION ./
		CONFIGURATIONS Release RelWithDebInfo Debug
	)
 
	install(FILES ${CMAKE_SOURCE_DIR}/dist/bin/plugins.cfg
		${CMAKE_SOURCE_DIR}/dist/bin/resources.cfg
		DESTINATION bin
		CONFIGURATIONS Release RelWithDebInfo Debug
	)
 
endif(UNIX)

# Setup testing
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIR})

# Add test cpp file
add_executable(runUnitTests
    ${TESTHDRS}
    ${TESTSRCS}
)

# Link test executable against gtest & gtest_main
target_link_libraries(runUnitTests ${GTEST_BOTH_LIBRARIES} ${OGRE_LIBRARIES} ${OGRE_Overlay_LIBRARIES})
set_target_properties(runUnitTests PROPERTIES COMPILE_DEFINITIONS "EXCLUDE_FROM_TEST")
add_test(
    NAME runUnitTests
    COMMAND runUnitTests
)
 
