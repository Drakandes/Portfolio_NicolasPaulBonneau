#include "stdafx.h"
#include "UserInterface.h"

UserInterface::UserInterface()
{
	if (!font.loadFromFile("Constantine.ttf"))
	{
		std::cout << "Error font user interface" << std::endl;
	}

	language = ListObjectsSingleton::instance()->GetCurrentLanguage();

	if (language == English_E)
	{
		ListNameInterfaces.push_back("Close");
		ListNameInterfaces.push_back("Skills");
		ListNameInterfaces.push_back("Craft");
		ListNameInterfaces.push_back("Armors");
		ListNameInterfaces.push_back("Classes");
		ListNameInterfaces.push_back("Gems");
		ListNameInterfaces.push_back("Talents");
		ListNameInterfaces.push_back("Inventory");
		ListNameInterfaces.push_back("Shop");
		ListNameInterfaces.push_back("Controls");
		ListNameInterfaces.push_back("Achievements");
		ListNameInterfaces.push_back("Pets");
		ListNameInterfaces.push_back("Feats");
	}
	else
	{
		ListNameInterfaces.push_back("Fermer");
		ListNameInterfaces.push_back("Sorts");
		ListNameInterfaces.push_back("Artisanat");
		ListNameInterfaces.push_back("Armures");
		ListNameInterfaces.push_back("Classes");
		ListNameInterfaces.push_back("Gemmes");
		ListNameInterfaces.push_back("Talents");
		ListNameInterfaces.push_back("Inventaire");
		ListNameInterfaces.push_back("Magasin");
		ListNameInterfaces.push_back("Contrôle");
		ListNameInterfaces.push_back("Défis ");
		ListNameInterfaces.push_back("Familiers");
		ListNameInterfaces.push_back("Exploits");
	}

#pragma region TextureInterfaceLoading
	if (true)
	{
		sf::Texture texture_of_interface;
		texture_of_interface.loadFromFile("IconePanelInterfaceV1.png");
		ListTextureInterface.push_back(texture_of_interface);
	}
	if (true)
	{
		sf::Texture texture_of_interface;
		texture_of_interface.loadFromFile("IconePanelInterfaceV2.png");
		ListTextureInterface.push_back(texture_of_interface);
	}

	texture_panel = ListTextureInterface[0];
#pragma endregion TextureInterfaceLoading

	sf::Vector2i counter{ 0,0 };
	sf::Vector2f window_size = ListObjectsSingleton::instance()->GetSizeWindow();
	for (int i = 0; i < number_interface; i++)
	{
		sprite_name_panel[i] = GlobalFunction::CreateSprite(position_first_panel + sf::Vector2f(window_size.x + size_panel.x*counter.x + counter.x * 5, size_panel.y*counter.y + 5 * counter.y), size_panel, texture_panel);
		text_name_panel[i] = GlobalFunction::CreateText(position_first_panel + sf::Vector2f(window_size.x + size_panel.x*counter.x + counter.x * 5, size_panel.y*counter.y + 5 * counter.y), ListNameInterfaces[i], font, size_letter_panel);
		text_name_panel[i].setFillColor(sf::Color::Color(108, 129, 197));
		text_name_panel[i].setStyle(sf::Text::Bold);
		counter.x++;
		if (counter.x == 2)
		{
			counter.x = 0;
			counter.y++;
		}
	}

	position_panel_style = position_first_panel + sf::Vector2f(window_size.x + size_panel.x/2 + 5, -size_panel.y - 5);
	position_text_style = position_first_panel + sf::Vector2f(window_size.x + size_panel.x/2 + 5, -size_panel.y - 5);
	text_style = GlobalFunction::CreateText(position_text_style, "Style", font, size_letter_panel);
	text_style.setFillColor(sf::Color::Color(108, 129, 197));
	text_style.setStyle(sf::Text::Bold);
	sprite_panel_style = GlobalFunction::CreateSprite(position_panel_style, size_panel, texture_panel);
}

UserInterface::~UserInterface()
{
}

bool UserInterface::IsPlaying()
{
	if (is_playing)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool UserInterface::IsToClose()
{
	return is_exiting;
}

void UserInterface::DrawToScreenMainInterface(sf::RenderWindow &window)
{
	if (!is_controls)
	{
		main_interface.DrawToScreen(window);
	}
	else
	{
		controls_interface.AnimationGestion();
		controls_interface.Draw(window,sf::Vector2f(0,0));
		if (controls_interface.Interaction(GlobalFunction::GetMousePosition(window,sf::Vector2f(0,0))) == "Back to menu")
		{
			is_controls = false;
		}
	}
}

void UserInterface::MainInterfaceInteraction(sf::RenderWindow &window)
{
	if (!is_controls)
	{
		sf::String interaction = main_interface.Interaction(window);

		if (interaction == "Play")
		{
			is_playing = true;
		}

		if (interaction == "Exit")
		{
			is_exiting = true;
		}

		if (interaction == "Controls")
		{
			is_controls = true;
		}
	}
	else
	{

	}
}

void UserInterface::WhilePlayingInterfaceGestion(std::shared_ptr<Player> player)
{
	if (clock_toggle_interface.getElapsedTime().asSeconds() >= 0.2 && player->GetCurrentOpenedInterface() != MageSelectionInterface_E)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
		{
			SoundGestion::instance()->AddSound("SoundMenuOpen.wav", 75, false);
			player->GiveNewOpenedInterface(SkillInterface_E);
			clock_toggle_interface.restart();
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
		{
			SoundGestion::instance()->AddSound("SoundMenuOpen.wav", 75, false);
			player->GiveNewOpenedInterface(ArmorInterface_E);
			clock_toggle_interface.restart();
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
		{
			SoundGestion::instance()->AddSound("SoundMenuOpen.wav", 75, false);
			player->GiveNewOpenedInterface(GemInterface_E);
			clock_toggle_interface.restart();
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::V))
		{
			SoundGestion::instance()->AddSound("SoundMenuOpen.wav", 75, false);
			player->GiveNewOpenedInterface(CraftingInterface_E);
			clock_toggle_interface.restart();
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
		{
			SoundGestion::instance()->AddSound("SoundMenuOpen.wav", 75, false);
			player->GiveNewOpenedInterface(ClassInterface_E);
			clock_toggle_interface.restart();
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
		{
			SoundGestion::instance()->AddSound("SoundMenuOpen.wav", 75, false);
			player->GiveNewOpenedInterface(TalentTree_E);
			clock_toggle_interface.restart();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
		{
			SoundGestion::instance()->AddSound("SoundMenuOpen.wav", 75, false);
			player->GiveNewOpenedInterface(VendorInterface_E);
			clock_toggle_interface.restart();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && player->GetCurrentOpenedInterface() == NoInterface_E)
		{
			SoundGestion::instance()->AddSound("SoundMenuOpen.wav", 75, false);
			player->GiveNewOpenedInterface(ControlInterface_E);
			clock_toggle_interface.restart();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && player->GetCurrentOpenedInterface() != NoInterface_E)
		{
			SoundGestion::instance()->AddSound("SoundMenuOpen.wav", 75, false);
			player->GiveNewOpenedInterface(NoInterface_E);
			clock_toggle_interface.restart();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::U))
		{
			SoundGestion::instance()->AddSound("SoundMenuOpen.wav", 75, false);
			player->GiveNewOpenedInterface(AchievementInterface_E);
			clock_toggle_interface.restart();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
		{
			SoundGestion::instance()->AddSound("SoundMenuOpen.wav", 75, false);
			player->GiveNewOpenedInterface(Inventory_E);
			clock_toggle_interface.restart();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
		{
			SoundGestion::instance()->AddSound("SoundMenuOpen.wav", 75, false);
			player->GiveNewOpenedInterface(PetInterface_E);
			clock_toggle_interface.restart();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::N))
		{
			SoundGestion::instance()->AddSound("SoundMenuOpen.wav", 75, false);
			player->GiveNewOpenedInterface(FeatInterface_E);
			clock_toggle_interface.restart();
		}
	}
}

void UserInterface::InitAllInterfaces(std::shared_ptr<Player> player)
{
	main_interface.Init(ListObjectsSingleton::instance()->GetCurrentLanguage());
	controls_interface.InitAll(false);
	skill_interface.InitSkillPlayer(player);
	armor_interface.InitArmorInterface(player);
	gem_interface.InitGemInterface(ListObjectsSingleton::instance()->GetCurrentLanguage());
	control_interface_in_game.InitAll(true);
}

void UserInterface::DrawToScreenOpenedInterfacesWhilePlaying(sf::RenderWindow &window, sf::Vector2f position_view_player, int opened_interface)
{
	UpdateStyleInterface();

	switch (opened_interface)
	{
	case SkillInterface_E:
		skill_interface.DrawToScreen(window, position_view_player);
		break;
	case ArmorInterface_E:
		armor_interface.DrawArmorInterface(window);
		break;
	case GemInterface_E:
		gem_interface.DrawGemInterface(window);
		break;
	case ClassInterface_E:
		class_menu_interface.Draw(window, position_view_player);
		break;
	case CraftingInterface_E:
		crafting_interface.Draw(window, position_view_player);
		break;
	case TalentTree_E:
		talent_interface.Draw(window, position_view_player);
		break;
	case Inventory_E:
		inventory_interface.Draw(window, position_view_player);
		break;
	case VendorInterface_E:
		vendor_interface.Draw(window, position_view_player);
		break;
	case ControlInterface_E:
		control_interface_in_game.Draw(window, position_view_player);
		break;
	case AchievementInterface_E:
		achievement_interface.Draw(window, position_view_player);
		break;
	case MageSelectionInterface_E:
		mage_selection_interface.Draw(window, position_view_player);
		break;
	case PetInterface_E:
		pet_interface.Draw(window, position_view_player);
		break;
	case FeatInterface_E :
		feat_interface.Draw(window, position_view_player);
		break;
	}

	if (display_panel)
	{
		sf::Vector2f window_size = ListObjectsSingleton::instance()->GetSizeWindow();

		sf::Vector2i counter{ 0,0 };
		for (int i = 0; i < number_interface; i++)
		{
			sprite_name_panel[i].setPosition(position_first_panel + sf::Vector2f(window_size.x + size_panel.x*counter.x + counter.x * 15, size_panel.y*counter.y + 15 * counter.y) + position_view_player);
			text_name_panel[i].setPosition(position_first_panel + sf::Vector2f(window_size.x + size_panel.x*counter.x + counter.x * 15, size_panel.y*counter.y + 15 * counter.y) + position_view_player);
			counter.x++;
			if (counter.x == 2)
			{
				counter.x = 0;
				counter.y++;
			}

			window.draw(sprite_name_panel[i]);
			window.draw(text_name_panel[i]);
		}

		position_panel_style = position_first_panel + sf::Vector2f(window_size.x + size_panel.x/2 + 5, -size_panel.y - 5) + position_view_player;
		position_text_style = position_first_panel + sf::Vector2f(window_size.x + size_panel.x/2 + 5, -size_panel.y - 8) + position_view_player;
		sprite_panel_style.setPosition(position_panel_style);
		text_style.setPosition(position_text_style);
		window.draw(sprite_panel_style);
		window.draw(text_style);
	}
}

void UserInterface::WhilePlayingAllInteractionInterface(sf::Vector2f mouse_position, sf::Vector2f position_view_player, std::shared_ptr<Player> player)
{
	int opened_interface = player->GetCurrentOpenedInterface();
	switch (opened_interface)
	{
	case SkillInterface_E:
		skill_interface.InteractionWithSkillInterface(mouse_position, position_view_player, player);
		break;
	case ArmorInterface_E:
		armor_interface.InteractionArmorInterface(mouse_position, position_view_player, player);
		break;
	case GemInterface_E:
		gem_interface.InteractionGemInterface(mouse_position, position_view_player, player);
		break;
	case ClassInterface_E:
		class_menu_interface.Update(player, mouse_position);
		break;
	case CraftingInterface_E:
		crafting_interface.Update(player, mouse_position);
		break;
	case TalentTree_E:
		talent_interface.Update(player, mouse_position);
		break;
	case Inventory_E:
		inventory_interface.Update(player, mouse_position);
		break;
	case VendorInterface_E:
		vendor_interface.Update(player, mouse_position);
		break;
	case ControlInterface_E:
		control_interface_in_game.Update(player, mouse_position);
		break;
	case AchievementInterface_E:
		achievement_interface.Update(player, mouse_position);
		break;
	case MageSelectionInterface_E:
		mage_selection_interface.Update(player, mouse_position);
		break;
	case PetInterface_E:
		pet_interface.Update(player, mouse_position);
		break;
	case FeatInterface_E:
		feat_interface.Update(player, mouse_position);
		break;
	}

	display_panel = false;

	if (opened_interface != NoInterface_E && opened_interface != ControlInterface_E  && opened_interface != MageSelectionInterface_E)
	{
		display_panel = true;
	}


	if (clock_click.getElapsedTime().asSeconds() >= 0.3)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (display_panel == true)
			{
				for (int i = 0; i < number_interface; i++)
				{
					if (sprite_name_panel[i].getGlobalBounds().contains(mouse_position))
					{
						player->GiveNewOpenedInterface(i);
					}
				}

				if (sprite_panel_style.getGlobalBounds().contains(mouse_position))
				{
					ListObjectsSingleton::instance()->IncreaseStyleInterface();
				}
			}

			clock_click.restart();
		}
	}
}

void UserInterface::UpdateStyleInterface()
{
	int style_received = ListObjectsSingleton::instance()->GetStyleInterface();
	if (style_received != current_style_interface)
	{
		current_style_interface = style_received;
		texture_panel = ListTextureInterface[current_style_interface];
		for (int i = 0; i < number_interface; i++)
		{
			sprite_name_panel[i].setTexture(texture_panel);
		}

		sprite_panel_style.setTexture(texture_panel);

		gem_interface.UpdateStyleInterface(current_style_interface);
		crafting_interface.UpdateStyleInterface(current_style_interface);
		skill_interface.UpdateStyleInterface(current_style_interface);
		armor_interface.UpdateStyleInterface(current_style_interface);
		talent_interface.UpdateStyleInterface(current_style_interface);
		class_menu_interface.UpdateStyleInterface(current_style_interface);
		inventory_interface.UpdateStyleInterface(current_style_interface);
		vendor_interface.UpdateStyleInterface(current_style_interface);
		achievement_interface.UpdateStyleInterface(current_style_interface);
		mage_selection_interface.UpdateStyleInterface(current_style_interface);
		pet_interface.UpdateStyleInterface(current_style_interface);
		feat_interface.UpdateStyleInterface(current_style_interface);
	}
}
