#include "stdafx.h"
#include "TutorialGestion.h"

TutorialGestion::TutorialGestion()
{
	if (language == English_E)
	{
		ListTextTutorial.push_back("You currently don't have a weapon equip. Press I to open your inventory and equip one or V to craft a weapon.");
		ListTextTutorial.push_back("You currently don't have a hat equip. Press I to open your inventory and equip one or X to buy a hat.");
		ListTextTutorial.push_back("You have unused talent points. Press T to open talent menu.");
		ListTextTutorial.push_back("You currently don't have any ring equip. Press I to open your inventory and equip one or kill a monster to obtain a loot bag.");
		ListTextTutorial.push_back("You currently don't have any gem equip. Press G to open the gem menu.");
		ListTextTutorial.push_back("You currently don't have any pet following you. Press P to open the pet menu.");
	}
	else
	{

		ListTextTutorial.push_back("Vous n'avez présentement aucune arme équipée. Appuyez sur I pour ouvrir votre inventaire et en équipper une ou V pour fabriquer une arme.");
		ListTextTutorial.push_back("Vous n'avez présentement aucun chapeau équipé. Appuyez sur I pour ouvrir votre inventaire et en équipper un ou X pour acheter un chapeua du magicien.");
		ListTextTutorial.push_back("Vous n'avez présentement des points de talent non-utilisés. Appuyez sur T pour ouvrir le menu des talents.");
		ListTextTutorial.push_back("Vous n'avez présentement aucune anneau équipée. Appuyez sur I pour ouvrir votre inventaire et en équipper un ou tuer un monstre pour recevoir un sac à butin.");
		ListTextTutorial.push_back("Vous n'avez présentement aucune gemme équipée. Appuyez sur G pour ouvrir le menu des gemmes.");
		ListTextTutorial.push_back("Vous n'avez présentement aucun familier qui vous suit. Appuyez sur P pour ouvrir le menu des familiers.");
	}
}
 
TutorialGestion::~TutorialGestion()
{
}

void TutorialGestion::GivePointerPlayer(std::shared_ptr<Player> player)
{
	pointer_player = player;
}

void TutorialGestion::Update(sf::Vector2f position_view_player)
{
	if(!all_tutorial_shown)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F9))
		{
			can_show_tutorial[tutorial_showing] = false;
			tutorial_shown[tutorial_showing] = true;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F10))
		{
			all_tutorial_shown = true;
		}

		sf::Vector2f window_size = ListObjectsSingleton::instance()->GetSizeWindow();
		position_tutorial.x = window_size.x - 150;

		if (!tutorial_shown[T_WeaponCraft])
		{
			if (pointer_player->GetCurrentWeapon() == NULL)
			{
				can_show_tutorial[T_WeaponCraft] = true;
			}
			else
			{
				tutorial_shown[T_WeaponCraft] = true;
				can_show_tutorial[T_WeaponCraft] = false;
				number_tutorial_shown++;
			}
		}

		if (!tutorial_shown[T_ArmorShop])
		{
			if (pointer_player->GetCurrentHat() == NULL)
			{
				can_show_tutorial[T_ArmorShop] = true;
			}
			else
			{
				tutorial_shown[T_ArmorShop] = true;
				can_show_tutorial[T_ArmorShop] = false;
				number_tutorial_shown++;
			}
		}

		if (!tutorial_shown[T_Talent])
		{
			if (pointer_player->GetPlayerArrayTalentPointsUsed()[PointsMax_E] <= 0)
			{
				can_show_tutorial[T_Talent] = true;
			}
			else
			{
				tutorial_shown[T_Talent] = true;
				can_show_tutorial[T_Talent] = false;
				number_tutorial_shown++;
			}
		}

		if (!tutorial_shown[T_Ring])
		{
			if (pointer_player->GetCurrentRing1() == NULL)
			{
				can_show_tutorial[T_Ring] = true;
			}
			else
			{
				tutorial_shown[T_Ring] = true;
				can_show_tutorial[T_Ring] = false;
				number_tutorial_shown++;
			}
		}

		if (!tutorial_shown[T_Ring])
		{
			if (pointer_player->GetCurrentRing1() == NULL)
			{
				can_show_tutorial[T_Ring] = true;
			}
			else
			{
				tutorial_shown[T_Ring] = true;
				can_show_tutorial[T_Ring] = false;
				number_tutorial_shown++;
			}
		}

		if (!tutorial_shown[T_GemEquip])
		{
			if (pointer_player->GetPlayerGemArray().size() == 0)
			{
				can_show_tutorial[T_GemEquip] = true;
			}
			else
			{
				tutorial_shown[T_GemEquip] = true;
				can_show_tutorial[T_GemEquip] = false;
				number_tutorial_shown++;
			}
		}

		if (!tutorial_shown[T_Pets])
		{
			if (pointer_player->GetCurrentPet() == NULL)
			{
				can_show_tutorial[T_Pets] = true;
			}
			else
			{
				tutorial_shown[T_Pets] = true;
				can_show_tutorial[T_Pets] = false;
				number_tutorial_shown++;
			}
		}

		if (number_tutorial_shown == number_tutorial)
		{
			all_tutorial_shown = true;
		}

		CheckNewTutorial();
		if (pointer_player->GetCurrentOpenedInterface() == NoInterface_E)
		{
			TextBoxGenerator::instance()->GenerateOneTextBox(listString, listIfCentered, listLetterSize, position_tutorial + position_view_player);
		}
	}
}

void TutorialGestion::CheckNewTutorial()
{
	if (!all_tutorial_shown)
	{
		bool is_showing_tutorial = false;
		for (int i = 0; i < number_tutorial; i++)
		{
			if (!tutorial_shown[i] && can_show_tutorial[i])
			{
				tutorial_showing = i;
				is_showing_tutorial = true;

				listLetterSize.clear();
				listString.clear();
				listIfCentered.clear();

				listLetterSize.push_back(16);
				listIfCentered.push_back(true);
				listString.push_back(ListTextTutorial[tutorial_showing]);

				if (language == English_E)
				{

					listString.push_back("Press F9 to close this advice or F10 to close all the advices.");
				}
				else
				{

					listString.push_back("Appuyez sur F9 pour fermer ce conseil ou F10 pour  fermer tous les conseils.");
				}
				listLetterSize.push_back(16);
				listIfCentered.push_back(true);
				break;
			}
		}

		if (!is_showing_tutorial)
		{
			tutorial_showing = T_Nothing;
			all_tutorial_shown = true;
		}
	}
}

TutorialGestion* TutorialGestion::s_instance1 = 0;