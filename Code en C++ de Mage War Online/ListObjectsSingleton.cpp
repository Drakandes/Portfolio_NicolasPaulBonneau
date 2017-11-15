#include "stdafx.h"
#include "ListObjectsSingleton.h"

ListObjectsSingleton::ListObjectsSingleton()
{
	std::cout << "ListObjectSingletonCreated" << std::endl;
	LoadParameter();
	CreateLists();
	CreateListStringTips();
	CreateListStringCharacteristic();
	CreateListStringAchiements();
}

ListObjectsSingleton::~ListObjectsSingleton()
{
}

void ListObjectsSingleton::CreateLists()
{
#pragma region ListArmor
	std::shared_ptr<A_BrokenArmor> BrokenArmor = std::shared_ptr<A_BrokenArmor>(new A_BrokenArmor(language));
	std::shared_ptr<A_ArmorOfTheWandering> ArmorOfTheWandering = std::shared_ptr<A_ArmorOfTheWandering>( new A_ArmorOfTheWandering(language));
	std::shared_ptr<A_BeginnerArmor> BeginnerArmor = std::shared_ptr<A_BeginnerArmor>( new A_BeginnerArmor(language));
	std::shared_ptr<A_RobeOfTheApprentice> RobeOfTheApprentice = std::shared_ptr<A_RobeOfTheApprentice>( new A_RobeOfTheApprentice(language));
	std::shared_ptr<A_RobeOfTheApprenticePlus> RobeOfTheApprenticePlus = std::shared_ptr<A_RobeOfTheApprenticePlus>( new A_RobeOfTheApprenticePlus(language));
	std::shared_ptr<A_RobeOfTheNovice> RobeOfTheNovice = std::shared_ptr<A_RobeOfTheNovice>( new A_RobeOfTheNovice(language));
	std::shared_ptr<A_RobeOfTheNovicePlus> RobeOfTheNovicePlus = std::shared_ptr<A_RobeOfTheNovicePlus>( new A_RobeOfTheNovicePlus(language));
	std::shared_ptr<A_RobeOfTheDevotee> RobeOfTheDevotee = std::shared_ptr<A_RobeOfTheDevotee>( new A_RobeOfTheDevotee(language));
	std::shared_ptr<A_RobeOfTheDevoteePlus> RobeOfTheDevoteePlus = std::shared_ptr<A_RobeOfTheDevoteePlus>( new A_RobeOfTheDevoteePlus(language));
	std::shared_ptr<A_RobeOfTheAcclaimed> RobeOfTheAcclaimed = std::shared_ptr<A_RobeOfTheAcclaimed>( new A_RobeOfTheAcclaimed(language));
	std::shared_ptr<A_RobeOfTheAcclaimedPlus> RobeOfTheAcclaimedPlus = std::shared_ptr<A_RobeOfTheAcclaimedPlus>( new A_RobeOfTheAcclaimedPlus(language));
	std::shared_ptr<A_RobeOfTheHunter> RobeOfTheHunter = std::shared_ptr<A_RobeOfTheHunter>( new A_RobeOfTheHunter(language));
	std::shared_ptr<A_RobeOfTheWarrior> RobeOfTheWarrior = std::shared_ptr<A_RobeOfTheWarrior>( new A_RobeOfTheWarrior(language));
	std::shared_ptr<A_RobeOfTheWarriorPlus> RobeOfTheWarriorPlus = std::shared_ptr<A_RobeOfTheWarriorPlus>( new A_RobeOfTheWarriorPlus(language));
	std::shared_ptr<A_RobeOfTheCommander> RobeOfTheCommander = std::shared_ptr<A_RobeOfTheCommander>( new A_RobeOfTheCommander(language));
	std::shared_ptr<A_RobeOfTheCommanderPlus> RobeOfTheCommanderPlus = std::shared_ptr<A_RobeOfTheCommanderPlus>( new A_RobeOfTheCommanderPlus(language));
	std::shared_ptr<A_RobeOfTheChief> RobeOfTheChief = std::shared_ptr<A_RobeOfTheChief>( new A_RobeOfTheChief(language));
	std::shared_ptr<A_RobeOfTheChiefPlus> RobeOfTheChiefPlus = std::shared_ptr<A_RobeOfTheChiefPlus>( new A_RobeOfTheChiefPlus(language));
	std::shared_ptr<A_RobeOfTheExpert> RobeOfTheExpert = std::shared_ptr<A_RobeOfTheExpert>( new A_RobeOfTheExpert(language));
	std::shared_ptr<A_RobeOfTheExpertPlus> RobeOfTheExpertPlus = std::shared_ptr<A_RobeOfTheExpertPlus>( new A_RobeOfTheExpertPlus(language));
	std::shared_ptr<A_RobeOfTheGuardian> RobeOfTheGuardian = std::shared_ptr<A_RobeOfTheGuardian>( new A_RobeOfTheGuardian(language));
	std::shared_ptr<A_RobeOfTheAncient> RobeOfTheAncient = std::shared_ptr<A_RobeOfTheAncient>( new A_RobeOfTheAncient(language));
	std::shared_ptr<A_RobeOfTheAncientElite> RobeOfTheAncientElite = std::shared_ptr<A_RobeOfTheAncientElite>( new A_RobeOfTheAncientElite(language));
	std::shared_ptr<A_RobeOfTheMaster> RobeOfTheMaster = std::shared_ptr<A_RobeOfTheMaster>( new A_RobeOfTheMaster(language));
	std::shared_ptr<A_RobeOfTheMasterElite> RobeOfTheMasterElite = std::shared_ptr<A_RobeOfTheMasterElite>( new A_RobeOfTheMasterElite(language));
	std::shared_ptr<A_RobeOfTheSpecialist> RobeOfTheSpecialist = std::shared_ptr<A_RobeOfTheSpecialist>( new A_RobeOfTheSpecialist(language));
	std::shared_ptr<A_RobeOfTheSpecialistElite> RobeOfTheSpecialistElite = std::shared_ptr<A_RobeOfTheSpecialistElite>( new A_RobeOfTheSpecialistElite(language));
	std::shared_ptr<A_RobeOfTheFabled> RobeOfTheFabled = std::shared_ptr<A_RobeOfTheFabled>( new A_RobeOfTheFabled(language));
	std::shared_ptr<A_RobeOfTheFabledElite> ARobeOfTheFabledElite = std::shared_ptr<A_RobeOfTheFabledElite>( new A_RobeOfTheFabledElite(language));
	std::shared_ptr<A_RobeOfTheWizard> RobeOfTheWizard = std::shared_ptr<A_RobeOfTheWizard>( new A_RobeOfTheWizard(language));
	std::shared_ptr<A_RobeOfTheWizardElite> RobeOfTheWizardElite = std::shared_ptr<A_RobeOfTheWizardElite>( new A_RobeOfTheWizardElite(language));
	std::shared_ptr<A_RobeOfTheScout> RobeOfTheScout = std::shared_ptr<A_RobeOfTheScout>( new A_RobeOfTheScout(language));
	std::shared_ptr<A_RobeOfTheScoutElite> RobeOfTheScoutElite = std::shared_ptr<A_RobeOfTheScoutElite>( new A_RobeOfTheScoutElite(language));
	listAllArmors.push_back(BrokenArmor);
	listAllArmors.push_back(ArmorOfTheWandering);
	listAllArmors.push_back(BeginnerArmor);
	listAllArmors.push_back(RobeOfTheApprentice);
	listAllArmors.push_back(RobeOfTheApprenticePlus);
	listAllArmors.push_back(RobeOfTheNovice);
	listAllArmors.push_back(RobeOfTheNovicePlus);
	listAllArmors.push_back(RobeOfTheDevotee);
	listAllArmors.push_back(RobeOfTheDevoteePlus);
	listAllArmors.push_back(RobeOfTheAcclaimed);
	listAllArmors.push_back(RobeOfTheAcclaimedPlus);
	listAllArmors.push_back(RobeOfTheHunter);
	listAllArmors.push_back(RobeOfTheWarrior);
	listAllArmors.push_back(RobeOfTheWarriorPlus);
	listAllArmors.push_back(RobeOfTheCommander);
	listAllArmors.push_back(RobeOfTheCommanderPlus);
	listAllArmors.push_back(RobeOfTheChief);
	listAllArmors.push_back(RobeOfTheChiefPlus);
	listAllArmors.push_back(RobeOfTheExpert);
	listAllArmors.push_back(RobeOfTheExpertPlus);
	listAllArmors.push_back(RobeOfTheGuardian);
	listAllArmors.push_back(RobeOfTheAncient);
	listAllArmors.push_back(RobeOfTheAncientElite);
	listAllArmors.push_back(RobeOfTheMaster);
	listAllArmors.push_back(RobeOfTheMasterElite);
	listAllArmors.push_back(RobeOfTheSpecialist);
	listAllArmors.push_back(RobeOfTheSpecialistElite);
	listAllArmors.push_back(RobeOfTheFabled);
	listAllArmors.push_back(ARobeOfTheFabledElite);
	listAllArmors.push_back(RobeOfTheWizard);
	listAllArmors.push_back(RobeOfTheWizardElite);
	listAllArmors.push_back(RobeOfTheScout);
	listAllArmors.push_back(RobeOfTheScoutElite);
#pragma endregion ListArmor
#pragma region ListSkill
	std::shared_ptr<SkillHugeFireball> skill_huge_fireball = std::shared_ptr<SkillHugeFireball>( new SkillHugeFireball(language));
	std::shared_ptr<SkillAblazeTheFire> skill_ablaze_the_fire = std::shared_ptr<SkillAblazeTheFire>( new SkillAblazeTheFire(language));
	std::shared_ptr<SkillTripleFireball> skill_triple_fireball = std::shared_ptr<SkillTripleFireball>( new SkillTripleFireball(language));
	std::shared_ptr<SkillAccurateShot> skill_accturate_shot = std::shared_ptr<SkillAccurateShot>( new SkillAccurateShot(language));
	std::shared_ptr<SkillBurningShot> SkillBurningShot_ = std::shared_ptr<SkillBurningShot>( new SkillBurningShot(language));
	std::shared_ptr<SkillIgnite> skill_ignite = std::shared_ptr<SkillIgnite>( new SkillIgnite(language));
	std::shared_ptr<SkillWarCry> skill_warcry = std::shared_ptr<SkillWarCry>( new SkillWarCry(language));
	std::shared_ptr<SkillLavaFloor> skill_lavafloor = std::shared_ptr<SkillLavaFloor>( new SkillLavaFloor(language));
	std::shared_ptr<SkillBlackVine> skill_black_vine = std::shared_ptr<SkillBlackVine>( new SkillBlackVine(language));
	std::shared_ptr<SkillFlowerBulbProtection> skill_bulb = std::shared_ptr<SkillFlowerBulbProtection>( new SkillFlowerBulbProtection(language));
	std::shared_ptr<SkillLeafZoneBoost> skill_leaf_zone = std::shared_ptr<SkillLeafZoneBoost>( new SkillLeafZoneBoost(language));
	std::shared_ptr<SkillWoodSkin> skill_wood_skin = std::shared_ptr<SkillWoodSkin>( new SkillWoodSkin(language));
	std::shared_ptr<SkillSwiftness> skill_swiftness = std::shared_ptr<SkillSwiftness>( new SkillSwiftness(language));
	std::shared_ptr<SkillLeafStorm> skill_leaf_storm = std::shared_ptr<SkillLeafStorm>( new SkillLeafStorm(language));
	std::shared_ptr<SkillRestrainingLeafBlade> skill_leaf_blade = std::shared_ptr<SkillRestrainingLeafBlade>( new SkillRestrainingLeafBlade(language));
	std::shared_ptr<SkillForcingBubble> forcing_bubble = std::shared_ptr<SkillForcingBubble>( new SkillForcingBubble(language));
	std::shared_ptr<SkillReplenishingWater> replenishing_water = std::shared_ptr<SkillReplenishingWater>( new SkillReplenishingWater(language));
	std::shared_ptr<SkillMagicalBubble> magical_bubble = std::shared_ptr<SkillMagicalBubble>( new SkillMagicalBubble(language));
	std::shared_ptr<SkillIceWall> ice_wall = std::shared_ptr<SkillIceWall>( new SkillIceWall(language));
	std::shared_ptr<SkillTeleportation> teleportation = std::shared_ptr<SkillTeleportation>( new SkillTeleportation(language));
	std::shared_ptr<SkillZoneHealing> zone_healing = std::shared_ptr<SkillZoneHealing>(new SkillZoneHealing(language));
	std::shared_ptr<SkillLiquidBody> liquid_body = std::shared_ptr<SkillLiquidBody>(new SkillLiquidBody(language));
	std::shared_ptr<SkillRockPike> rock_pike = std::shared_ptr<SkillRockPike>(new SkillRockPike(language));
	std::shared_ptr<SkillRockArmor> rock_armor = std::shared_ptr<SkillRockArmor>(new SkillRockArmor(language));
	std::shared_ptr<SkillReinforcement> reinforcement = std::shared_ptr<SkillReinforcement>(new SkillReinforcement(language));
	std::shared_ptr<SkillRockBelt> rock_belt = std::shared_ptr<SkillRockBelt>(new SkillRockBelt(language));
	std::shared_ptr<SkillRevive> revive = std::shared_ptr<SkillRevive>(new SkillRevive(language));
	std::shared_ptr<SkillUnderground> underground = std::shared_ptr<SkillUnderground>(new SkillUnderground(language));
	listAllSkill.push_back(skill_huge_fireball);
	listAllSkill.push_back(skill_ablaze_the_fire);
	listAllSkill.push_back(skill_triple_fireball);
	listAllSkill.push_back(skill_accturate_shot);
	listAllSkill.push_back(SkillBurningShot_);
	listAllSkill.push_back(skill_ignite);
	listAllSkill.push_back(skill_warcry);
	listAllSkill.push_back(skill_lavafloor);
	listAllSkill.push_back(skill_black_vine);
	listAllSkill.push_back(skill_bulb);
	listAllSkill.push_back(skill_leaf_zone);
	listAllSkill.push_back(skill_wood_skin);
	listAllSkill.push_back(skill_swiftness);
	listAllSkill.push_back(skill_leaf_storm);
	listAllSkill.push_back(skill_leaf_blade);
	listAllSkill.push_back(forcing_bubble);
	listAllSkill.push_back(replenishing_water);
	listAllSkill.push_back(magical_bubble); 
	listAllSkill.push_back(ice_wall);
	listAllSkill.push_back(teleportation);
	listAllSkill.push_back(zone_healing);
	listAllSkill.push_back(liquid_body);
	listAllSkill.push_back(rock_pike);
	listAllSkill.push_back(rock_armor);
	listAllSkill.push_back(reinforcement);
	listAllSkill.push_back(rock_belt);
	listAllSkill.push_back(revive);
	listAllSkill.push_back(underground);
#pragma endregion ListSkill
#pragma region ListGem
	std::shared_ptr<G_GemAttack> gem_attack = std::shared_ptr<G_GemAttack>( new G_GemAttack(language));
	std::shared_ptr<G_GemAvarice> gem_avarice = std::shared_ptr<G_GemAvarice>( new G_GemAvarice(language));
	std::shared_ptr<G_GemDefense> gem_defense = std::shared_ptr<G_GemDefense>( new G_GemDefense(language));
	std::shared_ptr<G_GemExperience> gem_experience = std::shared_ptr<G_GemExperience>( new G_GemExperience(language));
	std::shared_ptr<G_GemHonor> gem_honor = std::shared_ptr<G_GemHonor>( new G_GemHonor(language));
	std::shared_ptr<G_GemLife> gem_life = std::shared_ptr<G_GemLife>( new G_GemLife(language));
	std::shared_ptr<G_GemSwitfness> gem_swiftness = std::shared_ptr<G_GemSwitfness>( new G_GemSwitfness(language));
	std::shared_ptr<G_GemTime> gem_time = std::shared_ptr<G_GemTime>( new G_GemTime(language));

	ListAllGems.push_back(gem_attack);
	ListAllGems.push_back(gem_avarice);
	ListAllGems.push_back(gem_defense);
	ListAllGems.push_back(gem_experience);
	ListAllGems.push_back(gem_honor);
	ListAllGems.push_back(gem_life);
	ListAllGems.push_back(gem_swiftness);
	ListAllGems.push_back(gem_time);
#pragma endregion ListGem
#pragma region ListTalent
	std::shared_ptr<TalentEnraged> talent1 = std::shared_ptr<TalentEnraged>(new TalentEnraged(language));
	std::shared_ptr<TalentBoosted> talent2 = std::shared_ptr<TalentBoosted>(new TalentBoosted(language));
	std::shared_ptr<TalentBeastly> talent3 = std::shared_ptr<TalentBeastly>(new TalentBeastly(language));
	std::shared_ptr<TalentStoneMan> talent4 = std::shared_ptr<TalentStoneMan>(new TalentStoneMan(language));
	std::shared_ptr<TalentSwifty> talent5 = std::shared_ptr<TalentSwifty>(new TalentSwifty(language));
	std::shared_ptr<TalentRestless> talent6 = std::shared_ptr<TalentRestless>(new TalentRestless(language));
	std::shared_ptr<TalentNaturalBornKiller> talent7 = std::shared_ptr<TalentNaturalBornKiller>(new TalentNaturalBornKiller(language));
	std::shared_ptr<TalentOvercomeTheBarriers> talent8 = std::shared_ptr<TalentOvercomeTheBarriers>(new TalentOvercomeTheBarriers(language));
	std::shared_ptr<TalentHasty> talent9 = std::shared_ptr<TalentHasty>(new TalentHasty(language));
	std::shared_ptr<TalentHappyMeal> talent10 = std::shared_ptr<TalentHappyMeal>(new TalentHappyMeal(language));
	std::shared_ptr<TalentIronTip> talent11 = std::shared_ptr<TalentIronTip>(new TalentIronTip(language));
	std::shared_ptr<TalentImmuneSystem> talent12 = std::shared_ptr<TalentImmuneSystem>(new TalentImmuneSystem(language));
	std::shared_ptr<TalentAfterEffect> talent13 = std::shared_ptr<TalentAfterEffect>(new TalentAfterEffect(language));
	std::shared_ptr<TalentPeaceLoving> talent14 = std::shared_ptr<TalentPeaceLoving>(new TalentPeaceLoving(language));
	std::shared_ptr<TalentHardyMan> talent15 = std::shared_ptr<TalentHardyMan>(new TalentHardyMan(language));
	std::shared_ptr<TalentUnleashedPower> talent16 = std::shared_ptr<TalentUnleashedPower>(new TalentUnleashedPower(language));
	std::shared_ptr<TalentBlockade> talent17 = std::shared_ptr<TalentBlockade>(new TalentBlockade(language));
	std::shared_ptr<TalentTranquilizerAttack> talent18 = std::shared_ptr<TalentTranquilizerAttack>(new TalentTranquilizerAttack(language));
	std::shared_ptr<TalentSharpShooter> talent19 = std::shared_ptr<TalentSharpShooter>(new TalentSharpShooter(language));
	std::shared_ptr<TalentQuickAttack> talent20 = std::shared_ptr<TalentQuickAttack>(new TalentQuickAttack(language));
	std::shared_ptr<TalentDenseShield> talent21 = std::shared_ptr<TalentDenseShield>(new TalentDenseShield(language));
	std::shared_ptr<TalentHealthCare> talent22 = std::shared_ptr<TalentHealthCare>(new TalentHealthCare(language));
	std::shared_ptr<TalentUnstoppable> talent23 = std::shared_ptr<TalentUnstoppable>(new TalentUnstoppable(language));
	std::shared_ptr<TalentEnlightened> talent24 = std::shared_ptr<TalentEnlightened>(new TalentEnlightened(language));
	std::shared_ptr<TalentRampage> talent25 = std::shared_ptr<TalentRampage>(new TalentRampage(language));
	std::shared_ptr<TalentReinforcedShield> talent26 = std::shared_ptr<TalentReinforcedShield>(new TalentReinforcedShield(language));
	std::shared_ptr<TalentDisablingAttack> talent27 = std::shared_ptr<TalentDisablingAttack>(new TalentDisablingAttack(language));

	listAllTalents.push_back(talent1);
	listAllTalents.push_back(talent2);
	listAllTalents.push_back(talent3);
	listAllTalents.push_back(talent4);
	listAllTalents.push_back(talent5);
	listAllTalents.push_back(talent6);
	listAllTalents.push_back(talent7);
	listAllTalents.push_back(talent8);
	listAllTalents.push_back(talent9);
	listAllTalents.push_back(talent10);
	listAllTalents.push_back(talent11);
	listAllTalents.push_back(talent12);
	listAllTalents.push_back(talent13);
	listAllTalents.push_back(talent14);
	listAllTalents.push_back(talent15);
	listAllTalents.push_back(talent16);
	listAllTalents.push_back(talent17);
	listAllTalents.push_back(talent18);
	listAllTalents.push_back(talent19);
	listAllTalents.push_back(talent20);
	listAllTalents.push_back(talent21);
	listAllTalents.push_back(talent22);
	listAllTalents.push_back(talent23);
	listAllTalents.push_back(talent24);
	listAllTalents.push_back(talent25);
	listAllTalents.push_back(talent26);
	listAllTalents.push_back(talent27);
#pragma endregion ListTalent
}

void ListObjectsSingleton::CreateListStringTips()
{
	if (language == English_E)
	{
		sf::String str1 = "< Elite monsters give 2 times more loot! >";
		sf::String str2 = "< Don't forget to have a look at the skills once in a while! >";
		sf::String str3 = "< Try to fight elite monsters when they are alone! >";
		sf::String str4 = "< Never run away in an unknown region! >";
		sf::String str5 = "< Goats won't necessarly attack you, don't make them angry! >";
		sf::String str6 = "< You should fight monsters around 5 times your level! >";
		sf::String str7 = "< Nature always win, don't try to chop down every tree! >";
		sf::String str8 = "< Be aware of your environment, monsters can be hard to see sometime! >";
		sf::String str9 = "< Mix your stats, don't focus on only damage or defense! >";
		sf::String str10 = "< Even though the fire mage looks cool, there are also others mages! >";
		sf::String str11 = "< Take a break once in a while, don't let the rage fill you! >";
		sf::String str12 = "< Dodging is the key, don't try to absorb all the damage! >";
		sf::String str13 = "< Take your time, death is expensive! >";
		sf::String str14 = "< You can't avoid death! >";
		sf::String str15 = "< Sometimes, running is the best solution! >";
		sf::String str16 = "< Place your active skills on the lowest key numbers! >";
		sf::String str17 = "< Why are you still trying? Don't hurt yourself more! >";
		sf::String str18 = "< When you are sprinting, you are going 25% faster! >";
		sf::String str19 = "< Press left shift to sprint! >";

		listStringTips.push_back(str1);
		listStringTips.push_back(str2);
		listStringTips.push_back(str3);
		listStringTips.push_back(str4);
		listStringTips.push_back(str5);
		listStringTips.push_back(str6);
		listStringTips.push_back(str7);
		listStringTips.push_back(str8);
		listStringTips.push_back(str9);
		listStringTips.push_back(str10);
		listStringTips.push_back(str11);
		listStringTips.push_back(str12);
		listStringTips.push_back(str13);
		listStringTips.push_back(str14);
		listStringTips.push_back(str15);
		listStringTips.push_back(str16);
		listStringTips.push_back(str17);
		listStringTips.push_back(str18);
		listStringTips.push_back(str19);
	}
	else
	{
		sf::String str1 = "< Les monstres élites donnent deux fois plus de butin! >";
		sf::String str2 = "< N'oubliez pas de reparder le menu des sorts de temps en temps! >";
		sf::String str3 = "< Essayez de combattre les monstres élites lorsqu'ils sont seuls! >";
		sf::String str4 = "< Ne jamais s'échapper vers une région inexplorée! >";
		sf::String str5 = "< Les chèvres ne vous attaqueront pas nécessairement si elles vous voient, ne les énervez pas inutilement! >";
		sf::String str6 = "< Vous devriez combattre des monstres de niveau 5 fois supérieur au votre! >";
		sf::String str7 = "< La nature gagne toujours, n'essayez pas de couper tous les arbres! >";
		sf::String str8 = "< Soyez attentif à votre environnement, les monstres peuvent être difficile à apercevoir! >";
		sf::String str9 = "< Mélangez vos stats, ne vous concentrez pas seulement sur l'attaque ou la défense! >";
		sf::String str10 = "< Même si le mage de feu peut sembler fantastique, il y a d'autres mages! >";
		sf::String str11 = "< Prenez une pause de temps en temps, ne laissez pas la rage vous emporter! >";
		sf::String str12 = "< Esquiver est la clé, ne tentez pas d'absorber tous les dégâts! >";
		sf::String str13 = "< Prenez votre temps, la mort peut être coûteuse! >";
		sf::String str14 = "< Vous ne pouvez pas éviter la mort! >";
		sf::String str15 = "< Parfois, prendre ses jambes à son cou peut être la meilleure solution! >";
		sf::String str16 = "< Placez vos sorts actifs sur les nombres les plus petits du clavier! >";
		sf::String str17 = "< Pourquoi essayez-vous toujours? Ne vous faites pas plus de mal! >";
		sf::String str18 = "< Quand vous courez, vous êtes 25% plus rapide! >";
		sf::String str19 = "< Appuyez sur la touche Shift de gauche pour courir! >";

		listStringTips.push_back(str1);
		listStringTips.push_back(str2);
		listStringTips.push_back(str3);
		listStringTips.push_back(str4);
		listStringTips.push_back(str5);
		listStringTips.push_back(str6);
		listStringTips.push_back(str7);
		listStringTips.push_back(str8);
		listStringTips.push_back(str9);
		listStringTips.push_back(str10);
		listStringTips.push_back(str11);
		listStringTips.push_back(str12);
		listStringTips.push_back(str13);
		listStringTips.push_back(str14);
		listStringTips.push_back(str15);
		listStringTips.push_back(str16);
		listStringTips.push_back(str17);
		listStringTips.push_back(str18);
		listStringTips.push_back(str19);
	}
}

void ListObjectsSingleton::CreateListStringAchiements()
{
	if (language == English_E)
	{
		sf::String str1 = "Medecinator";
		sf::String str2 = "Ninja";
		sf::String str3 = "Marathoner";
		sf::String str4 = "Scout";
		sf::String str5 = "Hunter";
		sf::String str6 = "Explorer";
		sf::String str7 = "Sniper";
		sf::String str8 = "Survivor";
		sf::String str9 = "Master";
		sf::String str10 = "Rich";
		sf::String str11 = "Archmage";
		sf::String str12 = "Craftsman";

		listStringAchievements.push_back(str1);
		listStringAchievements.push_back(str2);
		listStringAchievements.push_back(str3);
		listStringAchievements.push_back(str4);
		listStringAchievements.push_back(str5);
		listStringAchievements.push_back(str6);
		listStringAchievements.push_back(str7);
		listStringAchievements.push_back(str8);
		listStringAchievements.push_back(str9);
		listStringAchievements.push_back(str10);
		listStringAchievements.push_back(str11);
		listStringAchievements.push_back(str12);
	}
	else
	{
		sf::String str1 = "Medecinateur";
		sf::String str2 = "Ninja";
		sf::String str3 = "Marathonien";
		sf::String str4 = "Scout";
		sf::String str5 = "Chasseur";
		sf::String str6 = "Exploreur";
		sf::String str7 = "Tireur d'Élite";
		sf::String str8 = "Survivant";
		sf::String str9 = "Maître";
		sf::String str10 = "Riche";
		sf::String str11 = "Archimage";
		sf::String str12 = "Artisan";

		listStringAchievements.push_back(str1);
		listStringAchievements.push_back(str2);
		listStringAchievements.push_back(str3);
		listStringAchievements.push_back(str4);
		listStringAchievements.push_back(str5);
		listStringAchievements.push_back(str6);
		listStringAchievements.push_back(str7);
		listStringAchievements.push_back(str8);
		listStringAchievements.push_back(str9);
		listStringAchievements.push_back(str10);
		listStringAchievements.push_back(str11);
		listStringAchievements.push_back(str12);
	}
}

void ListObjectsSingleton::CreateListStringCharacteristic()
{
	if (language == English_E)
	{
		std::vector<sf::String> listholder{ "Left-Handed","Simple-Minded","Broken Leg","Mingled","Allergic To Potion","Eye Disease","Close-Minded","Radioactive","Anonymous","Genetic Anomaly" };
		ListDrawback = listholder;

		if (true)
		{
			sf::String str1 = "Muscular";
			sf::String str2 = "Tolerant";
			sf::String str3 = "Young";
			sf::String str4 = "Athletic";
			sf::String str5 = "Magic Leg";
			sf::String str6 = "Smart";
			sf::String str7 = "Rich";
			sf::String str8 = "Magic Gift";
			sf::String str9 = "Rapid Metabolism";
			sf::String str10 = "Fierce";
			sf::String str11 = "Eagle Eye";
			sf::String str12 = "Artisan";
			sf::String str13 = "Energetic";
			sf::String str14 = "Quick Hand";
			sf::String str15 = "Passive";

			ListCharacteristicPros.push_back(str1);
			ListCharacteristicPros.push_back(str2);
			ListCharacteristicPros.push_back(str3);
			ListCharacteristicPros.push_back(str4);
			ListCharacteristicPros.push_back(str5);
			ListCharacteristicPros.push_back(str6);
			ListCharacteristicPros.push_back(str7);
			ListCharacteristicPros.push_back(str8);
			ListCharacteristicPros.push_back(str9);
			ListCharacteristicPros.push_back(str10);
			ListCharacteristicPros.push_back(str11);
			ListCharacteristicPros.push_back(str12);
			ListCharacteristicPros.push_back(str13);
			ListCharacteristicPros.push_back(str14);
			ListCharacteristicPros.push_back(str15);
		}

		if (true)
		{
			sf::String str1 = "Slim";
			sf::String str2 = "Sensitive";
			sf::String str3 = "Old";
			sf::String str4 = "Asthmatic";
			sf::String str5 = "Weak leg";
			sf::String str6 = "Stupid";
			sf::String str7 = "Poor";
			sf::String str8 = "Unaware";
			sf::String str9 = "Slow Metabolism";
			sf::String str10 = "Soft";
			sf::String str11 = "Nearsighted";
			sf::String str12 = "Intellectual";
			sf::String str13 = "Lazy";
			sf::String str14 = "Clumsy";
			sf::String str15 = "Aggressive";

			ListCharacteristicCons.push_back(str1);
			ListCharacteristicCons.push_back(str2);
			ListCharacteristicCons.push_back(str3);
			ListCharacteristicCons.push_back(str4);
			ListCharacteristicCons.push_back(str5);
			ListCharacteristicCons.push_back(str6);
			ListCharacteristicCons.push_back(str7);
			ListCharacteristicCons.push_back(str8);
			ListCharacteristicCons.push_back(str9);
			ListCharacteristicCons.push_back(str10);
			ListCharacteristicCons.push_back(str11);
			ListCharacteristicCons.push_back(str12);
			ListCharacteristicCons.push_back(str13);
			ListCharacteristicCons.push_back(str14);
			ListCharacteristicCons.push_back(str15);
		}
	}
	else
	{
		std::vector<sf::String> listholder{ "Gaucher","Simplet","Jambe Cassée","Confus","Allergique aux Potions","Maladie aux Yeux","Fermé d'Esprit","Radioactif","Anonyme","Anomalie Génétique" };
		ListDrawback = listholder;

		if (true)
		{
			sf::String str1 = "Musclé";
			sf::String str2 = "Tolérant";
			sf::String str3 = "Jeune";
			sf::String str4 = "Athlétique";
			sf::String str5 = "Jambe Magique";
			sf::String str6 = "Intelligent";
			sf::String str7 = "Riche";
			sf::String str8 = "Don Magique";
			sf::String str9 = "Métabolisme Rapide";
			sf::String str10 = "Féroce";
			sf::String str11 = "Oeil d'Aigle";
			sf::String str12 = "Artisan";
			sf::String str13 = "Énergique";
			sf::String str14 = "Mains Rapides";
			sf::String str15 = "Passif";

			ListCharacteristicPros.push_back(str1);
			ListCharacteristicPros.push_back(str2);
			ListCharacteristicPros.push_back(str3);
			ListCharacteristicPros.push_back(str4);
			ListCharacteristicPros.push_back(str5);
			ListCharacteristicPros.push_back(str6);
			ListCharacteristicPros.push_back(str7);
			ListCharacteristicPros.push_back(str8);
			ListCharacteristicPros.push_back(str9);
			ListCharacteristicPros.push_back(str10);
			ListCharacteristicPros.push_back(str11);
			ListCharacteristicPros.push_back(str12);
			ListCharacteristicPros.push_back(str13);
			ListCharacteristicPros.push_back(str14);
			ListCharacteristicPros.push_back(str15);
		}

		if (true)
		{
			sf::String str1 = "Svelte";
			sf::String str2 = "Sensible";
			sf::String str3 = "Vieux";
			sf::String str4 = "Asthmatique";
			sf::String str5 = "Jambe faible";
			sf::String str6 = "Stupide";
			sf::String str7 = "Pauvre";
			sf::String str8 = "Ignorant";
			sf::String str9 = "Métabolisme lent";
			sf::String str10 = "Doux";
			sf::String str11 = "Myope";
			sf::String str12 = "Intellectuel";
			sf::String str13 = "Paresseux";
			sf::String str14 = "Maladroit";
			sf::String str15 = "Aggresif";

			ListCharacteristicCons.push_back(str1);
			ListCharacteristicCons.push_back(str2);
			ListCharacteristicCons.push_back(str3);
			ListCharacteristicCons.push_back(str4);
			ListCharacteristicCons.push_back(str5);
			ListCharacteristicCons.push_back(str6);
			ListCharacteristicCons.push_back(str7);
			ListCharacteristicCons.push_back(str8);
			ListCharacteristicCons.push_back(str9);
			ListCharacteristicCons.push_back(str10);
			ListCharacteristicCons.push_back(str11);
			ListCharacteristicCons.push_back(str12);
			ListCharacteristicCons.push_back(str13);
			ListCharacteristicCons.push_back(str14);
			ListCharacteristicCons.push_back(str15);
		}
	}
}

std::vector<std::shared_ptr<A_ArmorBase>> ListObjectsSingleton::GetListArmor()
{
	return listAllArmors;
}

std::vector<std::shared_ptr<SkillBase>> ListObjectsSingleton::GetListSkill()
{
	return listAllSkill;
}

std::vector<std::shared_ptr<G_GemBase>> ListObjectsSingleton::GetListGem()
{
	return ListAllGems;
}

int ListObjectsSingleton::GetNewID()
{
	counter_id++;
	return counter_id - 1;
}

int ListObjectsSingleton::GetNewIDEquipment()
{
	counter_id_equipment++;
	return counter_id_equipment - 1;
}

sf::Vector2f ListObjectsSingleton::GetSizeWindow()
{
	return size_window;
}

void ListObjectsSingleton::ChangeSizeWindow(sf::Vector2f new_window_size)
{
	size_window = new_window_size;
}

sf::String ListObjectsSingleton::GetRandomStringTip()
{
	int random_string = GlobalFunction::getRandomRangeWithUnknownException(1, listStringTips.size(), listStringTipsAlreadyPassed);
	listStringTipsAlreadyPassed.push_back(random_string);
	return listStringTips[random_string - 1];
}

void ListObjectsSingleton::SaveParameter()
{
	std::ofstream ofs;
	ofs.open("Parameter.txt", std::ofstream::out | std::ofstream::trunc);
	ofs.close();

	std::ofstream myfile;
	myfile.open("Parameter.txt", std::fstream::app);
	myfile.seekp(std::ios::end);
	myfile << "ModifyAtYourOwnRisk";
	myfile << std::endl;
	myfile << std::endl;

	myfile << "Language";
	myfile << std::endl;
	myfile << " < ";

	std::string str("" + std::to_string(futur_language));
	myfile << str;
	myfile << std::string(" ");

	myfile << " > ";
	myfile << std::endl;

	myfile << "SaveIsUsed";
	myfile << std::endl;
	myfile << " < ";
	for (int i = 0; i < SaveIsUsed.size(); i++)
	{
		if (SaveIsUsed[i])
		{
			myfile << "true";
			myfile << std::string(" ");
		}
		else
		{
			myfile << "false";
			myfile << std::string(" ");
		}
	}
	myfile << " > ";
	myfile << std::endl;

	myfile << "Difficulties";
	myfile << std::endl;
	myfile << " < ";
	for (int i = 0; i < ListSaveDifficulty.size(); i++)
	{
		std::string str("" + std::to_string(ListSaveDifficulty[i]));
		myfile << str;
		myfile << std::string(" ");
	}
	myfile << " > ";
	myfile << std::endl;

	myfile << "ListMapLevel";
	myfile << std::endl;
	myfile << " < ";
	for (int i = 0; i < ListMapLevel.size(); i++)
	{
		std::string str("" + std::to_string(ListMapLevel[i]));
		myfile << str;
		myfile << std::string(" ");
	}
	myfile << " > ";
	myfile << std::endl;

	myfile.close();
}

void ListObjectsSingleton::LoadParameter()
{
	std::ifstream myfile("Parameter.txt");

	if (myfile.is_open())
	{
		std::string str;
		myfile >> str;

		if (str == "ModifyAtYourOwnRisk")
		{
			myfile >> str;
			if (str == "Language")
			{
				myfile >> str;
				if (str == "<")
				{
					int counter = 0;
					myfile >> str;
					while (str != ">")
					{
						int number = GlobalFunction::ConvertStringToInt(str);
						language = number;
						futur_language = number;
						counter++;
						myfile >> str;
					}
				}
			}

			myfile >> str;
			if (str == "SaveIsUsed")
			{
				myfile >> str;
				if (str == "<")
				{
					int counter = 0;
					myfile >> str;
					while (str != ">")
					{
						if (str == "true")
						{
							SaveIsUsed[counter] = true;
							counter++;
							myfile >> str;
						}
						else
						{
							SaveIsUsed[counter] = false;
							counter++;
							myfile >> str;
						}
					}
				}
			}

			myfile >> str;
			if (str == "Difficulties")
			{
				myfile >> str;
				if (str == "<")
				{
					int counter = 0;
					myfile >> str;
					while (str != ">")
					{
						int number = GlobalFunction::ConvertStringToInt(str);
						ListSaveDifficulty[counter] = number;
						counter++;
						myfile >> str;
					}
				}
			}

			myfile >> str;
			if (str == "ListMapLevel")
			{
				myfile >> str;
				if (str == "<")
				{
					int counter = 0;
					myfile >> str;
					while (str != ">")
					{
						int number = GlobalFunction::ConvertStringToInt(str);
						ListMapLevel[counter] = number;
						counter++;
						myfile >> str;
					}
				}
			}
		}
	}

	myfile.close();
}

void ListObjectsSingleton::SetCurrentSave(int save_number)
{ 
	current_save = save_number; 
	if (!SaveIsUsed[save_number])
	{
		SaveIsUsed[save_number] = true;
		ListSaveDifficulty[save_number] = game_mode;
	}
	else
	{
		game_mode = ListSaveDifficulty[save_number];
		std::cout << ListSaveDifficulty[save_number] << std::endl;
	}
}

void ListObjectsSingleton::IncreaseStyleInterface()
{
	if (style_interface + 1 == NUMBERSTYLEINTERFACE)
	{
		style_interface = 0;
	}
	else
	{
		style_interface++;
	}
}

ListObjectsSingleton* ListObjectsSingleton::s_instance1 = 0;

