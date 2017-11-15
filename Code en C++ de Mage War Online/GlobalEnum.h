#pragma once
#include "SpriteBase.h"
#include "DrawGestion.h"

enum Direction { Up, Right, Standing, Left, Down };
#define PI 3.14159266
#define Proportion 1
#define FPS_LIMIT 0.005
#define SPEED_PROPORTION 0.005/FPS_LIMIT
#define NUMBERSKILL 28
#define TIMERNOTIFICATION 4
#define TILESIZE 32
#define NUMBERSTYLEINTERFACE 2
 
enum Fragment {StrongFragment, EnchantedFragment, RunicFragment, AncientFragment, LostLegendaryFragment};
enum SkillSlots { FirstSkill, SecondSkill, ThirdSkill, FourthSkill, FifthSkill, SixthSkill, SeventhSkill, EighthSkill, NinethSkill };
enum ArmorBonus{A_HealthPerSecond,A_Damage,A_HealthArmor,A_AttackSpeed,A_HealthArmorDamage,A_Speed,A_Range,A_Cooldown};
enum Bonus {Nothing, HpRecovery, MovementSpeedPercent, DamagePercent, ExperiencePercent, DamageAddition, HealthAddition, DefenseAddition, CooldownReduction, MoneyPercent, HonorPercent, HealthPercent,AttackSpeedPercent, HpPercentRecovery,Immunity, DefensePercent, LifeSteal, StunReductionPercent,DamagePercentOverall,DamagePerLevel,HealthPerLevel,ArmorPerLevel,SpeedPerLevel,AttackSpeedPerLevel,CooldownRedutionPerLevel,Scared,HpRecoveryPercentIncrease,ShieldHpPercentRecovery,CantDie, ArmorOnShield, DamageReduction, ShieldCapacity};
enum Armors{RobeBroken,RobeWandering,RobeBeginner,RobeApprentice,RobeApprentiePlus,RobeNovice,RobeNovicePlus,RobeDevotee,RobeDevoteePlus,RobeAcclaimed,RobeAcclaimedPlus,RobeHunter,RobeWarrior,RobeWarriorPlus,RobeCommander,RobeCommanderPlus,RobeChief,RobeChiefPlus,RobeExpert,RobeExpertPlus,RobeGuardian,RobeAncient,RobeAncientElite,RobeMaster,RobeMasterElite,RobeSpecialist,RobeSpecialistElite,RobeFabled,RobeFabledElite,RobeWizard,RobeWizardElite,RobeScout,RobeScoutElite};
enum Gems{GemAttack,GemAvarice,GemDefense,GemExperience,GemHonor,GemLife,GemSwiftness,GemTime};
enum DavbheerPotions{AttackSpeedPotion, DamagePotion, MovementPotion, RegenerationPotion};
enum TypeIgnition{OnFireFromPassive,OnFireFromSkill,OnFireFromLavaFloor};
enum TypeSkill { PassiveSkill_E, ProjectileSkill_E, ZoneSkill_E, BuffSkill_E };
enum TpeSlowDebuff { StackableSlow_E, TranquilizerTalentSlow_E };
enum TypeProjectile{BasicAttackProjectile_E,SkillProjectile_E};
enum Skills{HugeFireballEnum,AblazeTheFireEnum,TripleFireballEnum,AccurateShotEnum,BurningShotEnum,IgniteEnum, WarCryEnum,LavaFloorEnum, BlackVineEnum, FlowerBulbProtectionEnum, LeafGuardZoneEnum, WoodSkinEnum, SwiftnessEnum, LeafStormEnum, RestrainingLeafBladeEnum, ForcingBubbleEnum, ReplenishingWaterEnum, MagicalBubbleEnum, IceWallEnum, TeleportationEnum,ZoneHealingEnum, LiquidBodyEnum, RockPikeEnum, RockArmorEnum, ReinforcementEnum, RockBeltEnum, ReviveEnum, UndergroundEnum};
enum Monsters{BlobEnum, DavbheerEnum, MiniGoatEnum, PenguinEnum, DemonEnum, SentryEnum, SquidEnum, SquidChildEnum,DummyEnum,FliesEnum,BombyEnum,WaelfonEnum,DarkMageEnum};
enum ForcePush{NoPush,WeakPush,NormalPush,StrongPush, ReallyStrongPush};
enum CollisionalObjectType{Nothing_E,Projectile_E,Monster_E,Player_E,NatureObject_E, Material_E,LootBag_E};
enum PlayerInventory{I_Material,I_Miscellaneous};
enum InventoryMaterial{IM_Stick, IM_Iron, IM_Ruby, IM_Emerald, IM_Topaz, IM_MagicSand};
enum InventotyMiscellaneous{IM_HealthPotion};
enum ClassPlayer{ClassFire, ClassGrass, ClassWater, ClassRock, NoClass};
enum TalentPointsUsed{PointsDamageTree_E, PointsDefenseTree_E, PointsUtilityTree_E,PointsMax_E}; 
enum Interfaces{NoInterface_E, SkillInterface_E, CraftingInterface_E, ArmorInterface_E, ClassInterface_E,GemInterface_E,TalentTree_E,Inventory_E,VendorInterface_E,ControlInterface_E,AchievementInterface_E,PetInterface_E,FeatInterface_E,MageSelectionInterface_E, PlayerInformationInterface_E};
enum Talents{Enraged_E,Boosted_E,Beastly_E,StoneMan_E,Swifty_E,Restless_E,NatureBornKiller_E,OvercomeTheBarriers_E,Hasty_E,HappyMeal_E,IronTip_E, ImmuneSystem_E,AfterEffect_E,PeaceLoving_E,HardyMan_E,UnleashedPower_E,Blockade_E,TranquilizerAttack_E,SharpShooter_E,QuickAttack_E,DenseShield_E, HealthCare_E,Unstoppable_E,Enlightened_E,Rampage_E,ReinforcedShield_E,DisablingAttack_E};
enum EquipmentCategory{RingEquipment_E,WeaponEquipment_E,WizardHatEquipment_E, BaseEquipment_E};
enum TypeWeapon{NormalWeapon_E,OffensiveWeapon_E, UtilityWeapon_E,DefensiveWeapon_E};
enum TypeWizardHat{NormalHat_E,OffensiveHat_E,DefensiveHat_E,UtilityHat_E};
enum GameMode{ChildishMode,BeginnerMode,IntermediateMode,ExpertMode};
enum MonsterEliteBonus{SecondLife_E,Regeneration_E,HastyMonster_E,Energized_E,PushImpact_E,Scary_E,DividedHealth_E,ElectricShot_E,Teleportation_E,HealingOrbs_E,Invisibility_E,Trap_E};
enum Achievements{TotalHealOneRun,NoDamageWhileCombat,OutOfSprintOneRun,MonsterOnRadar,MonsterKilledOneRun,MapFifthReached,MonsterHitOneRun,ReachLevelTen,GetFiveAchiemevents,SpendGoldOneRun,GetFiveSkillLevelTwo,CollectMaterialOneRun};
enum ActionAchievements{A_Heal,A_InCombat,A_OutOfSprint,A_NumberMonsterRadar,A_MonsterKilled,A_MapReachedLevel,A_MonsterHit,A_PlayerLevel,A_GoldSpent,A_NumberSkillLevelTwo,A_MaterialCollected};
enum Languages{English_E,French_E};
enum Saving{FirstSave_E,SecondSave_E,ThirdSave_E, NoSave_E};
enum Rarity{Common_E,Uncommon_E,Rare_E,Epic_E,Legendary_E};
enum SkillRunes{FirstRune_E,SecondRune_E,ThirdRune_E,NoRune_E};
enum MonsterGeneratorAction{MonsterGeneratorNothing,SpawnRandomNumberMonsters, FillSpawnsWithXMonsters};
enum PetAttributes{Power_E,Wisdom_E,Intelligence_E,Speed_E};
enum PetTypes{Ninja_E,Fairy_E, Knight_E,NoPet_E};
enum PetSkillType{P_BasicAttack,P_FirstSkill,P_FirstPassive,P_SecondSkill,P_SecondPassive};
enum FeatType{Slaughterer_E, Fighter_E,Hitman_E,Surviver_E,Veteran_E,Greedy_E,Shaman_E,Lord_E,Archmage_E,Talented_E};
enum ActionFeat { F_Kill, F_TimeBattle, F_KillElite, F_MapReached, F_LevelReached, F_MoneyReceived, F_PotionUsed, F_LegendaryGotten, F_SkillLeveled, F_Achievement};
enum TypeTutorial{T_WeaponCraft,T_ArmorShop, T_Talent,T_Ring,T_GemEquip,T_Pets, T_Nothing};
enum TypeBossFighting{NoBoss, BossViking, BossMolly};
