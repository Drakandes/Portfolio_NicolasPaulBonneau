#include "stdafx.h"
#include "FeatInterface.h"

FeatInterface::FeatInterface()
{
	if (!font.loadFromFile("Constantine.ttf"))
	{
		std::cout << "Error font feat interface" << std::endl;
	}

#pragma region TextureInterfaceLoading
	if (true)
	{
		sf::Texture texture_of_interface;
		texture_of_interface.loadFromFile("FeatInterfaceV1.png");
		ListTextureInterface.push_back(texture_of_interface);
	}
	if (true)
	{
		sf::Texture texture_of_interface;
		texture_of_interface.loadFromFile("FeatInterfaceV2.png");
		ListTextureInterface.push_back(texture_of_interface);
	}

	texture_interface = ListTextureInterface[0];
#pragma endregion TextureInterfaceLoading

	CreateListInformation();

	interface_feat = GlobalFunction::CreateSpriteWithoutOrigin(position_interface, size_interface, texture_interface);

	int holder = 0;
	for (int i = 0; i < number_feats; i++)
	{
		position_text_feat[i] = sf::Vector2f(position_first_text_feat.x, position_first_text_feat.y + 39 * i);
		text_feat[i] = GlobalFunction::CreateTextWithNoOrigin(position_text_feat[i], string_feat[i], font, 16);

		text_bonus_number[i] = GlobalFunction::CreateTextWithNoOrigin(position_text_feat[i], "Test", font, 16);
		text_best_number[i] = GlobalFunction::CreateTextWithNoOrigin(position_text_feat[i], "Test", font, 16);
		text_current_value_number[i] = GlobalFunction::CreateTextWithNoOrigin(position_text_feat[i], "Test", font, 16);
	}

	if (language == English_E)
	{
		text_name_interface = GlobalFunction::CreateText(position_name_interface, "Feats", font, 34);
		text_description = GlobalFunction::CreateTextWithNoOrigin(position_text_description, "Description", font, 19);
		text_current_value = GlobalFunction::CreateText(position_text_current_value, "Current", font, 19);
		text_best = GlobalFunction::CreateText(position_text_best, "Best", font, 19);
		text_bonus = GlobalFunction::CreateText(position_text_bonus, "Bonus", font, 19);
	}
	else
	{
		text_name_interface = GlobalFunction::CreateText(position_name_interface, "Exploits", font, 34);
		text_description = GlobalFunction::CreateTextWithNoOrigin(position_text_description, "Description", font, 19);
		text_current_value = GlobalFunction::CreateText(position_text_current_value, "Actuel", font, 19);
		text_best = GlobalFunction::CreateText(position_text_best, "Meilleur", font, 19);
		text_bonus = GlobalFunction::CreateText(position_text_bonus, "Bonus", font, 19);
	}
	text_name_interface.setFillColor(sf::Color::Color(108, 129, 197));
	text_description.setFillColor(sf::Color::Color(67, 88, 161));
	text_best.setFillColor(sf::Color::Color(67, 88, 161));
	text_current_value.setFillColor(sf::Color::Color(67, 88, 161));
	text_bonus.setFillColor(sf::Color::Color(67, 88, 161));
	text_name_interface.setStyle(sf::Text::Bold);
}

FeatInterface::~FeatInterface()
{
}

void FeatInterface::Draw(sf::RenderWindow &window, sf::Vector2f position_view_player)
{
	text_name_interface.setPosition(position_view_player + position_name_interface);
	interface_feat.setPosition(position_view_player + position_interface);
	text_description.setPosition(position_view_player + position_text_description);
	text_current_value.setPosition(position_view_player + position_text_current_value);
	text_best.setPosition(position_view_player + position_text_best);
	text_bonus.setPosition(position_view_player + position_text_bonus);

	window.draw(interface_feat);
	window.draw(text_name_interface);
	window.draw(text_description);
	window.draw(text_current_value);
	window.draw(text_best);
	window.draw(text_bonus);

	for (int i = 0; i < number_feats; i++)
	{
		text_feat[i].setPosition(position_text_feat[i] + position_view_player);
		window.draw(text_feat[i]);

		text_best_number[i].setPosition(position_text_feat[i] + position_view_player + sf::Vector2f(best_distance, 0));
		text_bonus_number[i].setPosition(position_text_feat[i] + position_view_player + sf::Vector2f(bonus_distance, 0));
		text_current_value_number[i].setPosition(position_text_feat[i] + position_view_player + sf::Vector2f(current_value_distance,0));
		window.draw(text_best_number[i]);
		window.draw(text_bonus_number[i]);
		window.draw(text_current_value_number[i]);
	}
}

void FeatInterface::Update(std::shared_ptr<Player> &player, sf::Vector2f mouse_position)
{
	std::vector<float> listFeatBonus = FeatGestion::instance()->GetListFeatBonus();
	std::vector<float> listFeatRecord = FeatGestion::instance()->GetListFeatRecord();
	std::vector<float> listFeatCurrentValue = FeatGestion::instance()->GetListFeatCurrentValue();

	for (int i = 0; i < number_feats; i++)
	{
		sf::String str_current_value;
		str_current_value = GlobalFunction::InsertNumberToString(str_current_value, listFeatCurrentValue[i], str_current_value.getSize());
		text_current_value_number[i].setString(str_current_value);

		sf::String str_best;
		str_best = GlobalFunction::InsertNumberToString(str_best, listFeatRecord[i], str_best.getSize());
		text_best_number[i].setString(str_best);

		sf::String str_bonus = "+";
		str_bonus = GlobalFunction::InsertNumberToStringIfFloat(str_bonus, listFeatBonus[i], str_bonus.getSize());
		str_bonus.insert(str_bonus.getSize(), "%");
		text_bonus_number[i].setString(str_bonus);
	}

	CreateRectangleInformation(mouse_position);
}

void FeatInterface::CheckPlayerAction(std::shared_ptr<Player> &player, sf::Vector2f mouse_position)
{
	if (clock_click.getElapsedTime().asSeconds() >= 0.15)
	{

	}
}

void FeatInterface::CreateRectangleInformation(sf::Vector2f mouse_position)
{
	for (int i = 0; i < number_feats; i++)
	{
		if (text_feat[i].getGlobalBounds().contains(mouse_position))
		{
			std::vector<int> listLetterSize;
			std::vector<sf::String> listString;
			std::vector<bool> listIfCentered;

			sf::String string1 = listStringFeatInformation[i];
			listString.push_back(string1);
			listLetterSize.push_back(16);
			listIfCentered.push_back(false);

			TextBoxGenerator::instance()->GenerateOneTextBox(listString, listIfCentered, listLetterSize, mouse_position);

		}
	}
}

void FeatInterface::CreateListInformation()
{
	if (language == English_E)
	{
		string_feat[0] = "Slaughterer";
		string_feat[1] = "Fighter";
		string_feat[2] = "Hitman";
		string_feat[3] = "Surviver";
		string_feat[4] = "Veteran";
		string_feat[5] = "Greedy";
		string_feat[6] = "Shaman";
		string_feat[7] = "Lord";
		string_feat[8] = "Archmage";
		string_feat[9] = "Talented";

		listStringFeatInformation[0] = "You get stronger as you kill monsters, over and over again. You get +0.2% overall damage for each monster killed.";
		listStringFeatInformation[1] = "The more you fight, the easier it is to stay alive in combat. You get +0.12% lifesteal for each minute passed in battle.";
		listStringFeatInformation[2] = "You get quicker at killing your targets after each hunt. You get +0.25 attack speed for each elite monster killed.";
		listStringFeatInformation[3] = "As you explore the world, it gets harder to kill you. You get +5% maximum health for each map passed through.";
		listStringFeatInformation[4] = "You are learning magic quicker each time you level up. You get +10% experience for each level reached.";
		listStringFeatInformation[5] = "Money comes with money. You get +1% gold for each 15 000  gold received.";
		listStringFeatInformation[6] = "Each potion you drink fulfills you with powerful energy. You get +0.25% more healing for each potion drank.";
		listStringFeatInformation[7] = "The more equipments you have, the mightier they feel. You get +1% increased stats on equipments for each legendery received.";
		listStringFeatInformation[8] = "Power comes with knowledge. You get +0.5% fragments for each level of your skills.";
		listStringFeatInformation[9] = "Achievements require toughness. You get +6% armor for each achiemvent succeeded.";
	}
	else
	{
		string_feat[0] = "Massacreur";
		string_feat[1] = "Combattant";
		string_feat[2] = "Buteur";
		string_feat[3] = "Survivant";
		string_feat[4] = "Vétéran";
		string_feat[5] = "Avide";
		string_feat[6] = "Chaman";
		string_feat[7] = "Seigneur";
		string_feat[8] = "Archimage";
		string_feat[9] = "Doué";

		listStringFeatInformation[0] = "Vous devenez de plus en plus fort à chaque monstre que vous tuez. Vous recevez +0.2% de dégâts totaux pour chaque monstre tué.";
		listStringFeatInformation[1] = "Plus vous combattez, plus il est facile de rester en vie pendant un combat. Vous recevez +0.12% de vol de vie pour chaque minute passée en combat.";
		listStringFeatInformation[2] = "Vous devenez plus rapide à tuer vos cibles après chaque chasse. Vous recevez +0.25 de vitesse d'attaque pour chaque monstre élite tué.";
		listStringFeatInformation[3] = "Plus vous explorez, plus il est difficile de vous tuer. Vous recevez +5% de vie totale pour chaque carte traversée.";
		listStringFeatInformation[4] = "Vous apprenez plus rapidement la magique à chaque niveau supérieur. Vous recevez +10% d'expérience en plus pour chaque niveau atteint.";
		listStringFeatInformation[5] = "L'argent vient avec de l'argent. Vous recevez +1% pièce d'or en plus pour chaque 15 000 pièces d'or reçues.";
		listStringFeatInformation[6] = "Chaque potion que vous buvez remplit d'une énergie puissante. Vous recevez +0.25% plus de soins pour chaque potion consommée.";
		listStringFeatInformation[7] = "Plus vous avez d'équipments, plus ils vous semblent puissant. Vous recevez +1% sur les bonus des équipments pour chaque légendaire obtenu.";
		listStringFeatInformation[8] = "La force vient avec la connaisance. Vous recevez +0.5% de framents en plus pour chaque niveau de vos sorts.";
		listStringFeatInformation[9] = "Les défis demande de l'endurance. Vous recevez +6% d'armure pour chaque défi réussi.";
	}
}

void FeatInterface::UpdateStyleInterface(int style)
{
	texture_interface = ListTextureInterface[style];
	interface_feat.setTexture(texture_interface);
}
