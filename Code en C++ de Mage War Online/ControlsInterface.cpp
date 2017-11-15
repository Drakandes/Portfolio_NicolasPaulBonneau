#include "stdafx.h"
#include "ControlsInterface.h"
#include "GlobalFunction.h"

ControlsInterface::ControlsInterface()
{
	if (!font.loadFromFile("Constantine.ttf"))
	{
		std::cout << "Error" << std::endl;
	}

	if (!player_texture.loadFromFile("Firemage_32.png"))
	{
		std::cout << "Error: Couldn't load Firemage texture" << std::endl;
	}

	rect_black = GlobalFunction::CreateRectangle(sf::Vector2f(ListObjectsSingleton::instance()->GetSizeWindow().x, ListObjectsSingleton::instance()->GetSizeWindow().y), sf::Vector2f(0, 0));
	rect_black.setFillColor(sf::Color::Black);
	if (language == English_E)
	{
		text_save = GlobalFunction::CreateText(position_text_save, "Save", font, 40);
		text_exit = GlobalFunction::CreateText(position_text_exit, "Exit", font, 40);

		string_shortcuts[0] = "Skills menu : ";
		string_shortcuts[1] = "Talents menu : ";
		string_shortcuts[2] = "Inventory : ";
		string_shortcuts[3] = "Shop : ";
		string_shortcuts[4] = "Crafting menu : ";
		string_shortcuts[5] = "Classes menu : ";
		string_shortcuts[6] = "Gems menu : ";
		string_shortcuts[7] = "Armors Menu : ";
		string_shortcuts[8] = "Pets Menu : ";
		string_shortcuts[9] = "Feats Menu : ";
	}
	else
	{ 
		text_save = GlobalFunction::CreateText(position_text_save, "Sauvegarder", font, 40);
		text_exit = GlobalFunction::CreateText(position_text_exit, "Quitter", font, 40);

		string_shortcuts[0] = "Menu des sorts : ";
		string_shortcuts[1] = "Menu des talents : ";
		string_shortcuts[2] = "Inventaire : ";
		string_shortcuts[3] = "Magasin : ";
		string_shortcuts[4] = "Menu de l'artisanat : ";
		string_shortcuts[5] = "Menu des classes : ";
		string_shortcuts[6] = "Menu des gemmes : ";
		string_shortcuts[7] = "Menu des armures : ";
		string_shortcuts[8] = "Menu des familers : ";
		string_shortcuts[9] = "Menu des exploits : ";
	}

	player_image_up.setTexture(player_texture);
	player_image_left.setTexture(player_texture);
	player_image_right.setTexture(player_texture);
	player_image_down.setTexture(player_texture);

	string_key_shortcuts[0] = "K";
	string_key_shortcuts[1] = "T";
	string_key_shortcuts[2] = "I";
	string_key_shortcuts[3] = "X";
	string_key_shortcuts[4] = "V";
	string_key_shortcuts[5] = "P";
	string_key_shortcuts[6] = "G";
	string_key_shortcuts[7] = "B";
	string_key_shortcuts[8] = "P";
	string_key_shortcuts[9] = "N";

	for (int i = 0; i < number_shortcuts; i++)
	{
		text_shortcuts[i] = GlobalFunction::CreateTextWithNoOrigin(position_first_text_shortcuts + sf::Vector2f(0, distance_between_shortcurts * i), string_shortcuts[i], font, character_size_24);
		text_key_shortcuts[i] = GlobalFunction::CreateTextWithNoOrigin(position_first_text_key_shortcuts + sf::Vector2f(0, distance_between_shortcurts * i), string_key_shortcuts[i], font, character_size_24);

	}

	if (language == English_E)
	{
		string_text_tips[0] = "Tips for beginners";
		string_text_tips[1] = "Tips for intermediates";
		string_text_tips[2] = "Tips for experts";
	}
	else
	{
		string_text_tips[0] = "Conseils pour les débutants";
		string_text_tips[1] = "Conseils pour les avancés";
		string_text_tips[2] = "Conseils pour les experts";
	}

	for (int i = 0; i < 3; i++)
	{
		text_tips[i] = GlobalFunction::CreateTextWithNoOrigin(position_first_text_tips + sf::Vector2f(0, 125 * i), string_text_tips[i], font, 35);
	}

	if (language == English_E)
	{
		text_language = GlobalFunction::CreateText(position_text_language, "Language", font, 40);
	}
	else
	{

		text_language = GlobalFunction::CreateText(position_text_language, "Langage", font, 40);
	}
}

ControlsInterface::~ControlsInterface()
{
}

void ControlsInterface::InitAll(bool init_in_game)
{
	in_game_interface = init_in_game;
	InitMovementControls();
	InitExitButton();
}

void ControlsInterface::InitMovementControls()
{
	controls_text.setString("Controls");
	controls_text.setCharacterSize(40);
	controls_text.setFont(font);
	controls_text.setOrigin(sf::Vector2f(controls_text.getGlobalBounds().width / 2, controls_text.getGlobalBounds().height / 2));
	controls_text.setPosition(position_title);

	control_movement.setString("Moving around : ");
	control_movement.setCharacterSize(character_size_24);
	control_movement.setFont(font);
	control_movement.setPosition(sf::Vector2f(275, 250));

	control_A.setString("A");
	control_A.setCharacterSize(character_size_24);
	control_A.setFont(font);
	control_A.setOrigin(sf::Vector2f(control_A.getGlobalBounds().width / 2, control_A.getGlobalBounds().height / 2));
	position_key_movement[A] = sf::Vector2f(513, 257);
	control_A.setPosition(position_key_movement[A]);
	control_A.setFillColor(sf::Color::Black);

	rect_control_A.setSize(sf::Vector2f(25, 25));
	rect_control_A.setOrigin(sf::Vector2f(rect_control_A.getSize().x / 2 - 1, rect_control_A.getSize().y/4 ));
	rect_control_A.setPosition(control_A.getPosition() - sf::Vector2f(1, 0));
	rect_control_A.setFillColor(sf::Color::White);

	control_S.setString("S");
	control_S.setCharacterSize(character_size_24);
	control_S.setFont(font);
	control_S.setOrigin(sf::Vector2f(control_S.getGlobalBounds().width / 2, control_S.getGlobalBounds().height / 2));
	position_key_movement[S] = sf::Vector2f(541, 257);
	control_S.setPosition(position_key_movement[S]);
	control_S.setFillColor(sf::Color::Black);

	rect_control_S.setSize(sf::Vector2f(25, 25));
	rect_control_S.setOrigin(sf::Vector2f(rect_control_S.getSize().x / 2 - 1, rect_control_S.getSize().y / 4));
	rect_control_S.setPosition(control_S.getPosition());
	rect_control_S.setFillColor(sf::Color::White);

	control_W.setString("W");
	control_W.setCharacterSize(character_size_24);
	control_W.setFont(font);
	control_W.setOrigin(sf::Vector2f(control_W.getGlobalBounds().width / 2, control_W.getGlobalBounds().height / 2));
	position_key_movement[W] = sf::Vector2f(541, 230);
	control_W.setPosition(position_key_movement[W]);
	control_W.setFillColor(sf::Color::Black);

	rect_control_W.setSize(sf::Vector2f(25, 25));
	rect_control_W.setOrigin(sf::Vector2f(rect_control_W.getSize().x / 2 - 1, rect_control_W.getSize().y / 4));
	rect_control_W.setPosition(control_W.getPosition() - sf::Vector2f(1, 0));
	rect_control_W.setFillColor(sf::Color::White);

	control_D.setString("D");
	control_D.setCharacterSize(character_size_24);
	control_D.setFont(font);
	control_D.setOrigin(sf::Vector2f(control_W.getGlobalBounds().width / 2, control_W.getGlobalBounds().height / 2));
	position_key_movement[D] = sf::Vector2f(570, 257);
	control_D.setPosition(position_key_movement[D]);
	control_D.setFillColor(sf::Color::Black);

	rect_control_D.setSize(sf::Vector2f(25, 25));
	rect_control_D.setOrigin(sf::Vector2f(rect_control_D.getSize().x / 2 - 1, rect_control_D.getSize().y / 4));
	rect_control_D.setPosition(control_D.getPosition() - sf::Vector2f(3,0));
	rect_control_D.setFillColor(sf::Color::White);

	player_image_down.setOrigin(sf::Vector2f(player_image_size_x / 2, player_image_size_y / 2));
	position_sprite_movement[S] = sf::Vector2f(625, 262);
	player_image_down.setPosition(position_sprite_movement[S]);

	player_image_left.setOrigin(sf::Vector2f(player_image_size_x / 2, player_image_size_y / 2));
	position_sprite_movement[A] = sf::Vector2f(600, 262);
	player_image_left.setPosition(position_sprite_movement[A]);

	player_image_up.setOrigin(sf::Vector2f(player_image_size_x / 2, player_image_size_y / 2));
	position_sprite_movement[W] = sf::Vector2f(625, 229);
	player_image_up.setPosition(position_sprite_movement[W]);

	player_image_right.setOrigin(sf::Vector2f(player_image_size_x / 2, player_image_size_y / 2));
	position_sprite_movement[D] = sf::Vector2f(650, 262);
	player_image_right.setPosition(position_sprite_movement[D]);

}

void ControlsInterface::AnimationGestion()
{
	if (player_animation_clock.getElapsedTime().asSeconds() >= 0.1)
	{
		player_image_up.setTextureRect(sf::IntRect(player_image_size_x * source_x, 0*player_image_size_y, player_image_size_x, player_image_size_y));

		player_image_down.setTextureRect(sf::IntRect(player_image_size_x * source_x, 4*player_image_size_y, player_image_size_x, player_image_size_y));

		player_image_left.setTextureRect(sf::IntRect(player_image_size_x * source_x, 3*player_image_size_y, player_image_size_x, player_image_size_y));

		player_image_right.setTextureRect(sf::IntRect(player_image_size_x * source_x, 1*player_image_size_y, player_image_size_x, player_image_size_y));

		source_x++;
		if (source_x >= 6)
		{
			source_x = 0;
		}

		player_animation_clock.restart();
	}
}

void ControlsInterface::InitExitButton()
{
	sf::Vector2f exit_button_text_position{ 800,700 };
	text_exit_button = GlobalFunction::CreateText(exit_button_text_position, "Back to menu", font, 48);
}

void ControlsInterface::Draw(sf::RenderWindow &window,sf::Vector2f position_view_player)
{
	sf::Vector2f window_size = ListObjectsSingleton::instance()->GetSizeWindow();
	position_text_save.x = window_size.x - 175;
	position_text_save.y = window_size.y - 100;
	position_text_exit.y = window_size.y - 100;
	position_title.x = window_size.x / 2;
	position_text_resolution.x = window_size.x / 2;
	position_text_resolution.y = window_size.y - 50;
	position_text_language.x = window_size.x / 2;
	position_text_language.y = window_size.y - 100;
	rect_black.setSize(window_size);

	controls_text.setPosition(position_title + position_view_player);
	rect_control_A.setPosition(position_key_movement[A] + position_view_player);
	rect_control_S.setPosition(position_key_movement[S] + position_view_player);
	rect_control_D.setPosition(position_key_movement[D] + position_view_player);
	rect_control_W.setPosition(position_key_movement[W] + position_view_player);
	control_movement.setPosition(position_text_moving_around + position_view_player);
	control_A.setPosition(position_key_movement[A] + position_view_player);
	control_S.setPosition(position_key_movement[S] + position_view_player);
	control_W.setPosition(position_key_movement[W] + position_view_player);
	control_D.setPosition(position_key_movement[D] + position_view_player);
	player_image_up.setPosition(position_sprite_movement[W] + position_view_player);
	player_image_left.setPosition(position_sprite_movement[A] + position_view_player);
	player_image_right.setPosition(position_sprite_movement[D] + position_view_player);
	player_image_down.setPosition(position_sprite_movement[S] + position_view_player);
	rect_black.setPosition( position_view_player);
	text_save.setPosition(position_text_save + position_view_player);
	text_exit.setPosition(position_text_exit + position_view_player);
	text_resolution.setPosition(position_text_resolution + position_view_player);
	text_language.setPosition(position_text_language + position_view_player);

	if (text_exit.getGlobalBounds().contains(GlobalFunction::GetMousePosition(window,position_view_player)))
	{
		text_exit.setFillColor(sf::Color::Blue);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			window.close();
		}
	}
	else
	{
		text_exit.setFillColor(sf::Color::White);
	}

	window.draw(rect_black);
	window.draw(rect_control_A);
	window.draw(rect_control_S);
	window.draw(rect_control_D);
	window.draw(rect_control_W);
	window.draw(controls_text);
	window.draw(control_movement);
	window.draw(control_A);
	window.draw(control_S);
	window.draw(control_W);
	window.draw(control_D);
	window.draw(player_image_up);
	window.draw(player_image_down);
	window.draw(player_image_left);
	window.draw(player_image_right);
	if (!in_game_interface)
	{
		window.draw(text_exit_button);
	}
	else
	{
		window.draw(text_exit);
		window.draw(text_save);
		//window.draw(text_resolution);
		window.draw(text_language);
	}

	for (int i = 0; i < number_shortcuts; i++)
	{
		text_shortcuts[i].setPosition(position_first_text_shortcuts + sf::Vector2f(0, distance_between_shortcurts * i) + position_view_player);
		text_key_shortcuts[i].setPosition(position_first_text_key_shortcuts + sf::Vector2f(0, distance_between_shortcurts * i) + position_view_player);

		window.draw(text_shortcuts[i]);
		window.draw(text_key_shortcuts[i]);
	}

	for (int i = 0; i < 3; i++)
	{
		text_tips[i] .setPosition(position_first_text_tips + sf::Vector2f(0, 125 * i) + position_view_player);
		window.draw(text_tips[i]);
	}
}

void ControlsInterface::Update(std::shared_ptr<Player> &player, sf::Vector2f mouse_position)
{
	sf::Vector2f window_size = ListObjectsSingleton::instance()->GetSizeWindow();
	sf::String str_resolution = "Resolution : ";
	str_resolution = GlobalFunction::InsertNumberToString(str_resolution, window_size.x, str_resolution.getSize());
	str_resolution.insert(str_resolution.getSize(), " x ");
	str_resolution = GlobalFunction::InsertNumberToString(str_resolution, window_size.y, str_resolution.getSize());
	text_resolution.setString(str_resolution);

	sf::String string_language;
	if (language == English_E && !language_switched)
	{
		string_language = "Language : English";
	}
	else if (language == English_E && language_switched)
	{
		string_language = "Language : French";
	}
	else if (language == French_E && !language_switched)
	{
		string_language = "Langage : Français";
	}
	else
	{
		string_language = "Langage : Anglais";
	}
	text_language.setString(string_language);
	text_language.setOrigin(text_language.getGlobalBounds().width / 2, text_language.getGlobalBounds().height / 2);

	if (!do_once)
	{
		do_once != do_once;
		player_ptr = player;
	}
	player_ptr = player;
	AnimationGestion();
	CreateRectInformation(mouse_position);
	Interaction(mouse_position);
}

void ControlsInterface::CreateRectInformation(sf::Vector2f mouse_position)
{
	if (text_tips[Beginner].getGlobalBounds().contains(mouse_position))
	{
		std::vector<int> listLetterSize;
		std::vector<sf::String> listString;
		std::vector<bool> listIfCentered;

		if (language == English_E)
		{
			sf::String string1 = "- Make sure to quickly buy a weapon and a hat. They will both provide you great bonuses.";
			sf::String string2 = "- Check regularly if you can updrage any skill. Skills greatly increase your combat potential.";
			sf::String string3 = "- Always have at least 2 health potions so you can quickly heal when in need. Also, you should always drink health potion when out of combat for the most effectiveness.";
			sf::String string4 = "- Attack monsters one at a time. Don't let them overwhelm you.";
			sf::String string5 = "- Dying is part of the game. However, you have to learn from your mistakes. It's useless to try again and again the same thing!";
			listString.push_back(string1);
			listString.push_back(string2);
			listString.push_back(string3);
			listString.push_back(string4);
			listString.push_back(string5);
		}
		else
		{
			sf::String string1 = "- Assurez-vous de vous procurer rapidement un arme et un chapeau de magicien. Ils vont vous apporter de grands bonus.";
			sf::String string2 = "- Regardez souvent si vous pouvez augmenter vos sorts. Les sorts accruent énormément votre potentiel au combat.";
			sf::String string3 = "- Ayez toujours sur vous 2 potions de vie afin de pouvoir vous soigner rapidement au besoin. De plus, vous devriez tenter le plus possible de boire les potions de vie lorsque vous êtes hors-combat pour la plus grande efficacité.";
			sf::String string4 = "- Attaquez les monstres un à la fois, ne les laissez pas vous submerger.";
			sf::String string5 = "- Mourir fait parti du jeu. Cependant, vous devez apprendre de vos erreurs. C'est inutile de toujours tenter la même chose si elle ne fonctionne pas!";
			listString.push_back(string1);
			listString.push_back(string2);
			listString.push_back(string3);
			listString.push_back(string4);
			listString.push_back(string5);
		}

		listLetterSize.push_back(16);
		listLetterSize.push_back(16);
		listLetterSize.push_back(16);
		listLetterSize.push_back(16);
		listLetterSize.push_back(16);
		listIfCentered.push_back(false);
		listIfCentered.push_back(false);
		listIfCentered.push_back(false);
		listIfCentered.push_back(false);
		listIfCentered.push_back(false);

		TextBoxGenerator::instance()->GenerateOneTextBoxWithSize(listString, listIfCentered, listLetterSize, mouse_position, 100);
	}
	else if (text_tips[Intermediate].getGlobalBounds().contains(mouse_position))
	{
		std::vector<int> listLetterSize;
		std::vector<sf::String> listString;
		std::vector<bool> listIfCentered;

		if (language == English_E)
		{
			sf::String string1 = "- Try to diversify your build. Don't only go for damage, you won't last long. Lifesteal is a great way to stay alive in long battle.";
			sf::String string2 = "- Many armors have 2 variants, choose the one that suit your style.";
			sf::String string3 = "- Pick your class according to the skills you use the most.";
			sf::String string4 = "- Cooldown reduction can greatly increase your damage and movement speed can greatly increase your survivability.";
			sf::String string5 = "- Hunt the monsters you feel safe fighting against, each monster has his own pros and cons.";
			listString.push_back(string1);
			listString.push_back(string2);
			listString.push_back(string3);
			listString.push_back(string4);
			listString.push_back(string5);
		}
		else
		{
			sf::String string1 = "- Essayez de diversifier votre build. Ne vous concentrez pas seulement sur vos dégâts, vous ne survivrez pas longtemps! Le vol de vie peut être une façon de compenser.";
			sf::String string2 = "- Plusieurs armures possèdent deux variantes, choississez celle qui s'harmonise le plus à votre style.";
			sf::String string3 = "- Choississez votre classe selon les sorts que vous utilisez le plus.";
			sf::String string4 = "- Le temps de latence peut grandement augmenter vos dégâts et la vitesse de déplacement peut vous aider à survivre.";
			sf::String string5 = "- Chassez les monstres que vous avez de la facilité à combattre, chaque monstre possède ses avantages et ses défauts.";
			listString.push_back(string1);
			listString.push_back(string2);
			listString.push_back(string3);
			listString.push_back(string4);
			listString.push_back(string5);
		}

		listLetterSize.push_back(16);
		listLetterSize.push_back(16);
		listLetterSize.push_back(16);
		listLetterSize.push_back(16);
		listLetterSize.push_back(16);
		listIfCentered.push_back(false);
		listIfCentered.push_back(false);
		listIfCentered.push_back(false);
		listIfCentered.push_back(false);
		listIfCentered.push_back(false);

		TextBoxGenerator::instance()->GenerateOneTextBoxWithSize(listString, listIfCentered, listLetterSize, mouse_position, 100);
	}
	else if (text_tips[Expert].getGlobalBounds().contains(mouse_position))
	{
		std::vector<int> listLetterSize;
		std::vector<sf::String> listString;
		std::vector<bool> listIfCentered;

		if (language == English_E)
		{
			sf::String string1 = "- The monster difficulty is increasing exponentially. Same for the experience and the money received by killing them.";
			sf::String string2 = "- When using 2 skills that can stun, try to chain them one after the other.";
			sf::String string3 = "- Balance your armor and your maximum health. Armor is substracted from the damage you receive while health is the quantity of damage you can receive.";
			sf::String string4 = "- Don't forget to upgrade your equipments once in a while and focus on upgrading the ones with the less effective stats.";
			sf::String string5 = "- Go around the map. The closer you are from the center of the map, the stronger the monsters will be.";
			listString.push_back(string1);
			listString.push_back(string2);
			listString.push_back(string3);
			listString.push_back(string4);
			listString.push_back(string5);
		}
		else
		{
			sf::String string1 = "- La difficulté des monstres augmente exponentiellement. Il est de même pour leurs butins.";
			sf::String string2 = "- Si vous utilisez deux sorts qui peuvent étourdir, tentez de les appliquer un après l'autre.";
			sf::String string3 = "- Balancez votre armure et votre vie totale. L'armure est soustraitre aux dégâts que vous recevez tandis que la vie est la quantité de dégâts totales que vous pouvez subir.";
			sf::String string4 = "- N'oubliez pas de changer votre équipement de temps en temps et de vous concentrez sur les pièces avec le moins de bénéfices.";
			sf::String string5 = "- Circulez autour de la carte. Le plus près vous êtes du centre, le plus fort seront les ennemies.";
			listString.push_back(string1);
			listString.push_back(string2);
			listString.push_back(string3);
			listString.push_back(string4);
			listString.push_back(string5);
		}

		listLetterSize.push_back(16);
		listLetterSize.push_back(16);
		listLetterSize.push_back(16);
		listLetterSize.push_back(16);
		listLetterSize.push_back(16);
		listIfCentered.push_back(false);
		listIfCentered.push_back(false);
		listIfCentered.push_back(false);
		listIfCentered.push_back(false);
		listIfCentered.push_back(false);

		TextBoxGenerator::instance()->GenerateOneTextBoxWithSize(listString, listIfCentered, listLetterSize, mouse_position, 100);
	}
	else if (text_language.getGlobalBounds().contains(mouse_position))
	{
		std::vector<int> listLetterSize;
		std::vector<sf::String> listString;
		std::vector<bool> listIfCentered;
		if (language == English_E)
		{
			sf::String string1 = "-Appuyez pour changer en Français.";
			sf::String string2 = "-Vous devez redémarrer le jeu afin que les changements puissent s'effectuer.";
			listString.push_back(string1);
			listString.push_back(string2);
		}
		else
		{
			sf::String string1 = "-Click to switch to English.";
			sf::String string2 = "-You must restart the game to apply the changes.";
			listString.push_back(string1);
			listString.push_back(string2);
		}

		listLetterSize.push_back(16);
		listLetterSize.push_back(16);
		listIfCentered.push_back(false);
		listIfCentered.push_back(false);

		TextBoxGenerator::instance()->GenerateOneTextBoxWithSize(listString, listIfCentered, listLetterSize, mouse_position, 100);
	}
}

sf::String ControlsInterface::Interaction(sf::Vector2f mouse_position)
{
	sf::String interaction;
	sf::RectangleShape mouse_rectangle;
	mouse_rectangle.setSize(sf::Vector2f(1, 1));
	mouse_rectangle.setPosition(mouse_position);

	if (clock_click.getElapsedTime().asSeconds() >= 0.15)
	{
		if (mouse_rectangle.getGlobalBounds().intersects(text_exit_button.getGlobalBounds()))
		{
			text_exit_button.setCharacterSize(60);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				interaction = "Back to menu";
				SoundGestion::instance()->AddSound("SoundMenuClick.wav", 45, false);
			}
			else
			{
				interaction = "nothing";
			}
			clock_click.restart();
			return interaction;
		}
		else
		{
			text_exit_button.setCharacterSize(48);
		}

		if (text_save.getGlobalBounds().contains(mouse_position))
		{
			text_save.setFillColor(sf::Color::Blue);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				player_ptr->SaveInformations();
				clock_click.restart();
				SoundGestion::instance()->AddSound("SoundMenuClick.wav", 45, false);
			}
		}
		else
		{
			text_save.setFillColor(sf::Color::White);
		}

		if (text_language.getGlobalBounds().contains(mouse_position))
		{
			text_language.setFillColor(sf::Color::Blue);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (language == English_E && !language_switched)
				{
					ListObjectsSingleton::instance()->ChangeCurrentLanguage(French_E);
					language_switched = !language_switched;
				}
				else if(language == English_E && language_switched)
				{
					ListObjectsSingleton::instance()->ChangeCurrentLanguage(English_E);
					language_switched = !language_switched;
				}
				else if (language == French_E && !language_switched)
				{
					ListObjectsSingleton::instance()->ChangeCurrentLanguage(English_E);
					language_switched = !language_switched;
				}
				else
				{
					ListObjectsSingleton::instance()->ChangeCurrentLanguage(French_E);
					language_switched = !language_switched;
				}
				SoundGestion::instance()->AddSound("SoundMenuClick.wav", 45, false);
				clock_click.restart();

			}
		}
		else
		{
			text_language.setFillColor(sf::Color::White);
		}

		/*if (text_resolution.getGlobalBounds().contains(mouse_position))
		{
			text_resolution.setFillColor(sf::Color::Blue);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				sf::Vector2f window_size = ListObjectsSingleton::instance()->GetSizeWindow();
				if (window_size == sf::Vector2f(1600, 800))
				{
					ListObjectsSingleton::instance()->ChangeSizeWindow(sf::Vector2f(1900, 1600));
				}
				else
				{
					ListObjectsSingleton::instance()->ChangeSizeWindow(sf::Vector2f(1600, 800));
				}
				clock_click.restart();
			}
		}
		else
		{
			text_resolution.setFillColor(sf::Color::White);
		}*/
	}

	interaction = "nothing";
	return interaction;
}
