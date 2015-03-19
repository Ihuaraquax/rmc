#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=MinGW-Windows
CND_DLIB_EXT=dll
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/AiTile.o \
	${OBJECTDIR}/AiTileAdjacentSetter.o \
	${OBJECTDIR}/AllDecals.o \
	${OBJECTDIR}/AllEntities.o \
	${OBJECTDIR}/Attributes.o \
	${OBJECTDIR}/BloodSplatter.o \
	${OBJECTDIR}/BuffRod.o \
	${OBJECTDIR}/Button.o \
	${OBJECTDIR}/Chest.o \
	${OBJECTDIR}/Chestplate.o \
	${OBJECTDIR}/CollisionDetector.o \
	${OBJECTDIR}/Coordinates.o \
	${OBJECTDIR}/Decal.o \
	${OBJECTDIR}/DistanceBuffer.o \
	${OBJECTDIR}/Door.o \
	${OBJECTDIR}/Entity.o \
	${OBJECTDIR}/Equipment.o \
	${OBJECTDIR}/EquipmentLoader.o \
	${OBJECTDIR}/EquipmentUI.o \
	${OBJECTDIR}/Explosion.o \
	${OBJECTDIR}/ExplosiveBarrel.o \
	${OBJECTDIR}/Explosives.o \
	${OBJECTDIR}/Floor.o \
	${OBJECTDIR}/GenericBuffer.o \
	${OBJECTDIR}/Greaves.o \
	${OBJECTDIR}/Grenade.o \
	${OBJECTDIR}/HUD.o \
	${OBJECTDIR}/Helmet.o \
	${OBJECTDIR}/Image.o \
	${OBJECTDIR}/Inventory.o \
	${OBJECTDIR}/KeyboardControl.o \
	${OBJECTDIR}/Map.o \
	${OBJECTDIR}/Menu.o \
	${OBJECTDIR}/Missle.o \
	${OBJECTDIR}/Module.o \
	${OBJECTDIR}/ModuleFactory.o \
	${OBJECTDIR}/ModuleTile.o \
	${OBJECTDIR}/Monster.o \
	${OBJECTDIR}/MonsterLoader.o \
	${OBJECTDIR}/MouseControl.o \
	${OBJECTDIR}/Obstacle.o \
	${OBJECTDIR}/Player.o \
	${OBJECTDIR}/Projectile.o \
	${OBJECTDIR}/ProjectileFactory.o \
	${OBJECTDIR}/RemoteCharges.o \
	${OBJECTDIR}/Room.o \
	${OBJECTDIR}/RoomFactory.o \
	${OBJECTDIR}/Session.o \
	${OBJECTDIR}/Spawner.o \
	${OBJECTDIR}/TextDisplayer.o \
	${OBJECTDIR}/TileFactory.o \
	${OBJECTDIR}/TimedBuffer.o \
	${OBJECTDIR}/Turret.o \
	${OBJECTDIR}/UsableItem.o \
	${OBJECTDIR}/UsableItemLoader.o \
	${OBJECTDIR}/UsableObject.o \
	${OBJECTDIR}/Wall.o \
	${OBJECTDIR}/WallFactory.o \
	${OBJECTDIR}/Weapon.o \
	${OBJECTDIR}/WeaponLoader.o \
	${OBJECTDIR}/WeaponUI.o \
	${OBJECTDIR}/configurator.o \
	${OBJECTDIR}/main.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-lallegro-5.0.10-monolith-mt

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/rmcv02.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/rmcv02.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/rmcv02.exe ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/AiTile.o: AiTile.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/AiTile.o AiTile.cpp

${OBJECTDIR}/AiTileAdjacentSetter.o: AiTileAdjacentSetter.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/AiTileAdjacentSetter.o AiTileAdjacentSetter.cpp

${OBJECTDIR}/AllDecals.o: AllDecals.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/AllDecals.o AllDecals.cpp

${OBJECTDIR}/AllEntities.o: AllEntities.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/AllEntities.o AllEntities.cpp

${OBJECTDIR}/Attributes.o: Attributes.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Attributes.o Attributes.cpp

${OBJECTDIR}/BloodSplatter.o: BloodSplatter.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/BloodSplatter.o BloodSplatter.cpp

${OBJECTDIR}/BuffRod.o: BuffRod.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/BuffRod.o BuffRod.cpp

${OBJECTDIR}/Button.o: Button.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Button.o Button.cpp

${OBJECTDIR}/Chest.o: Chest.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Chest.o Chest.cpp

${OBJECTDIR}/Chestplate.o: Chestplate.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Chestplate.o Chestplate.cpp

${OBJECTDIR}/CollisionDetector.o: CollisionDetector.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/CollisionDetector.o CollisionDetector.cpp

${OBJECTDIR}/Coordinates.o: Coordinates.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Coordinates.o Coordinates.cpp

${OBJECTDIR}/Decal.o: Decal.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Decal.o Decal.cpp

${OBJECTDIR}/DistanceBuffer.o: DistanceBuffer.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/DistanceBuffer.o DistanceBuffer.cpp

${OBJECTDIR}/Door.o: Door.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Door.o Door.cpp

${OBJECTDIR}/Entity.o: Entity.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Entity.o Entity.cpp

${OBJECTDIR}/Equipment.o: Equipment.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Equipment.o Equipment.cpp

${OBJECTDIR}/EquipmentLoader.o: EquipmentLoader.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/EquipmentLoader.o EquipmentLoader.cpp

${OBJECTDIR}/EquipmentUI.o: EquipmentUI.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/EquipmentUI.o EquipmentUI.cpp

${OBJECTDIR}/Explosion.o: Explosion.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Explosion.o Explosion.cpp

${OBJECTDIR}/ExplosiveBarrel.o: ExplosiveBarrel.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/ExplosiveBarrel.o ExplosiveBarrel.cpp

${OBJECTDIR}/Explosives.o: Explosives.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Explosives.o Explosives.cpp

${OBJECTDIR}/Floor.o: Floor.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Floor.o Floor.cpp

${OBJECTDIR}/GenericBuffer.o: GenericBuffer.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/GenericBuffer.o GenericBuffer.cpp

${OBJECTDIR}/Greaves.o: Greaves.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Greaves.o Greaves.cpp

${OBJECTDIR}/Grenade.o: Grenade.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Grenade.o Grenade.cpp

${OBJECTDIR}/HUD.o: HUD.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/HUD.o HUD.cpp

${OBJECTDIR}/Helmet.o: Helmet.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Helmet.o Helmet.cpp

${OBJECTDIR}/Image.o: Image.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Image.o Image.cpp

${OBJECTDIR}/Inventory.o: Inventory.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Inventory.o Inventory.cpp

${OBJECTDIR}/KeyboardControl.o: KeyboardControl.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/KeyboardControl.o KeyboardControl.cpp

${OBJECTDIR}/Map.o: Map.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Map.o Map.cpp

${OBJECTDIR}/Menu.o: Menu.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Menu.o Menu.cpp

${OBJECTDIR}/Missle.o: Missle.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Missle.o Missle.cpp

${OBJECTDIR}/Module.o: Module.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Module.o Module.cpp

${OBJECTDIR}/ModuleFactory.o: ModuleFactory.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/ModuleFactory.o ModuleFactory.cpp

${OBJECTDIR}/ModuleTile.o: ModuleTile.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/ModuleTile.o ModuleTile.cpp

${OBJECTDIR}/Monster.o: Monster.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Monster.o Monster.cpp

${OBJECTDIR}/MonsterLoader.o: MonsterLoader.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/MonsterLoader.o MonsterLoader.cpp

${OBJECTDIR}/MouseControl.o: MouseControl.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/MouseControl.o MouseControl.cpp

${OBJECTDIR}/Obstacle.o: Obstacle.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Obstacle.o Obstacle.cpp

${OBJECTDIR}/Player.o: Player.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Player.o Player.cpp

${OBJECTDIR}/Projectile.o: Projectile.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Projectile.o Projectile.cpp

${OBJECTDIR}/ProjectileFactory.o: ProjectileFactory.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/ProjectileFactory.o ProjectileFactory.cpp

${OBJECTDIR}/RemoteCharges.o: RemoteCharges.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/RemoteCharges.o RemoteCharges.cpp

${OBJECTDIR}/Room.o: Room.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Room.o Room.cpp

${OBJECTDIR}/RoomFactory.o: RoomFactory.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/RoomFactory.o RoomFactory.cpp

${OBJECTDIR}/Session.o: Session.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Session.o Session.cpp

${OBJECTDIR}/Spawner.o: Spawner.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Spawner.o Spawner.cpp

${OBJECTDIR}/TextDisplayer.o: TextDisplayer.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/TextDisplayer.o TextDisplayer.cpp

${OBJECTDIR}/TileFactory.o: TileFactory.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/TileFactory.o TileFactory.cpp

${OBJECTDIR}/TimedBuffer.o: TimedBuffer.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/TimedBuffer.o TimedBuffer.cpp

${OBJECTDIR}/Turret.o: Turret.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Turret.o Turret.cpp

${OBJECTDIR}/UsableItem.o: UsableItem.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/UsableItem.o UsableItem.cpp

${OBJECTDIR}/UsableItemLoader.o: UsableItemLoader.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/UsableItemLoader.o UsableItemLoader.cpp

${OBJECTDIR}/UsableObject.o: UsableObject.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/UsableObject.o UsableObject.cpp

${OBJECTDIR}/Wall.o: Wall.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Wall.o Wall.cpp

${OBJECTDIR}/WallFactory.o: WallFactory.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/WallFactory.o WallFactory.cpp

${OBJECTDIR}/Weapon.o: Weapon.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Weapon.o Weapon.cpp

${OBJECTDIR}/WeaponLoader.o: WeaponLoader.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/WeaponLoader.o WeaponLoader.cpp

${OBJECTDIR}/WeaponUI.o: WeaponUI.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/WeaponUI.o WeaponUI.cpp

${OBJECTDIR}/configurator.o: configurator.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/configurator.o configurator.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/rmcv02.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
