#include "Objects_Manager.h"
#include "Generic_Object.h"
#include "Text_Printer.h"
#include "Dialog_Engine.h"
#include "Character.h"
#include "Map.h"

void GObject::routine()
{
	if (!type.compare("ENEMY")) {
		for (int i = 0; i < flags.size(); i++) {
			if (!flags[i].compare("PATTERN")) {
				switch (movingUnit.mainDirection) {
				case 1:
					if (!Objects_Manager::findObject(std::to_string
					(Map::getIdObject(movingUnit.hitBox.y + movingUnit.hitBox.h + 1, 0, movingUnit.hitBox.x, 0)))
						->type.compare("PATTERN")) {
						movingUnit.speedY = movingUnit.xCSPEED;
					}
					break;
				case -1:

					break;

				case 2:

					break;

				case -2:

					break;
				}


				break;
			}
		}
	}
	//movingUnit.move();
}

void GObject::trigger()
{
	flagTrigger = 1;
	for (int i = 0; i < targetnames.size(); i++) {
		if (!Objects_Manager::findObject(targetnames[i])->flagTrigger)
			Objects_Manager::findObject(targetnames[i])->trigger();
	}
	if (!type.compare("BUTTON")) {
		if (!flags[0].compare("CONTACT")) {
			if (!Text_Printer::busy) 
				Text_Printer::addToQueue(content);
		}
	}

	if (!type.compare("DIALOG")) {
		if (!Text_Printer::busy) {
			if (content[0] == '|') {
				DialogEngine::dialogSelector(content);
			}
			else
				Text_Printer::addToQueue(content);
		}
	}

	if (!type.compare("TELEPORT")) {
		Character::movingUnit.teleport(x, y);
	}

	flagTrigger = 0;
}

bool GObject::checkFlag(std::string flag)
{
	for (auto i = flags.begin(); i != flags.end(); ++i) {
		if (!i->compare(flag)) return true;
	}
	return false;
}
