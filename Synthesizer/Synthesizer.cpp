#include <iostream>
#include <cstdlib>
#include <windows.h>
#include "RtMidi.h"

using namespace std;

RtMidiOut* midiout;
std::vector<unsigned char> message;
int octave;

void initialize()
{
	message.push_back(192);
	message.push_back(0);
	midiout->sendMessage(&message);
	message[0] = 176;
	message[1] = 7;
	message.push_back(127);
	midiout->sendMessage(&message);
	octave = 4;
}

void setInstrument(int instrument)
{
	message[0] = 192;
	message[1] = instrument;
	midiout->sendMessage(&message);
}

void setVolume(int volume)
{
	message[0] = 176;
	message[1] = 7;
	message[2] = volume;
	midiout->sendMessage(&message);
}

void noteOn(int note)
{
	message[0] = 144;
	message[1] = note;
	message[2] = 90;
	midiout->sendMessage(&message);
}

void noteOff(int note)
{
	message[0] = 128;
	message[1] = note;
	message[2] = 40;
	midiout->sendMessage(&message);
}

void printKeyboard()
{
	cout << "|   |   | |   |   |   |   | |   | |   |   |   |   | |   |   |\n";
	cout << "|   | S | | D |   |   | G | | H | | J |   |   | L | | ; |   |\n";
	cout << "|   |___| |___|   |   |___| |___| |___|   |   |___| |___|   |\n";
	cout << "|     |     |     |     |     |     |     |     |     |     |\n";
	cout << "|  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |  /  |\n";
	cout << "|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|\n\n";
	cout << "Q:Quit      U:Change volume      I:Change instrument      O:Change octave\n\n";
}

void printInstruments()
{
	cout << "0:Acoustic Grand Piano  1:Bright Acoustic Piano 2:Electric Grand Piano  3:Honky-Tonk Piano\n";
	cout << "4:Electric Piano 1      5:Electric Piano 2      6:Harpsichord           7:Clavi\n";
	cout << "8:Celesta               9:Glockenspiel          10:Music Box            11:Vibraphone\n";
	cout << "12:Marimba              13:Xylophone            14:Tubular Bells        15:Dulcimer\n";
	cout << "16:Drawbar Organ        17:Percussive Organ     18:Rock Organ           19:Church Organ\n";
	cout << "20:Reed Organ           21:Accordion            22:Harmonica            23:Tango Accordion\n";
	cout << "24:Acoustic Guit Nylon  25:Acoustic Guit Steel  26:Electric Guitar Jazz 27:Electric Guitar Clean\n";
	cout << "28:Electric Guit Muted  29:Overdriven Guitar    30:Distortion Guitar    31:Guitar Harmonics\n";
	cout << "32:Acoustic Bass        33:Electric Bass Finger 34:Electric Bass Pick   35:Fretless Bass\n";
	cout << "36:Slap Bass 1          37:Slap Bass 2          38:Synth Bass 1         39:Synth Bass 2\n";
	cout << "40:Violin               41:Viola                42:Cello                43:Contrabass\n";
	cout << "44:Tremolo Strings      45:Pizzicato Strings    46:Orchestral Harp      47:Timpani\n";
	cout << "48:String Ensemble 1    49:String Ensemble 2    50:Synth Strings 1      51:Synth Strings 2\n";
	cout << "52:Choir Aahs           53:Voice Oohs           54:Synth Voice          55:Orchestra Hit\n";
	cout << "56:Trumpet              57:Trombone             58:Tuba                 59:Muted Trumpet\n";
	cout << "60:French Horn          61:Brass Section        62:Synth Brass 1        63:Synth Brass 2\n";
	cout << "64:Soprano Sax          65:Alto Sax             66:Tenor Sax            67:Baritone Sax\n";
	cout << "68:Oboe                 69:English Horn         70:Bassoon              71:Clarinet\n";
	cout << "72:Piccolo              73:Flute                74:Recorder             75:Pan Flute\n";
	cout << "76:Blown Bottle         77:Shakuhachi           78:Whistle              79:Ocarina\n";
	cout << "80:Lead 1 Square        81:Lead 2 Sawtooth      82:Lead 3 Calliope      83:Lead 4 Chiff\n";
	cout << "84:Lead 5 Charang       85:Lead 6 Voice         86:Lead 7 Fifths        87:Lead 8 Bass + Lead\n";
	cout << "88:Pad 1 New Age        89:Pad 2 Warm           90:Pad 3 Polysynth      91:Pad 4 Choir\n";
	cout << "92:Pad 5 Bowed          93:Pad 6 Metallic       94:Pad 7 Halo           95:Pad 8 Sweep\n";
	cout << "96:FX 1 Rain            97:FX 2 Soundtrack      98:FX 3 Crystal         99:FX 4 Atmosphere\n";
	cout << "100:FX 5 Brightness     101:FX 6 Goblins        102:FX 7 Echoes         103:FX 8 Sci-Fi\n";
	cout << "104:Sitar               105:Banjo               106:Shamisen            107:Koto\n";
	cout << "108:Kalimba             109:Bagpipe             110:Fiddle              111:Shanai\n";
	cout << "112:Tinkle Bell         113:Agogo               114:Steel Drums         115:Woodblock\n";
	cout << "116:Taiko Drum          117:Melodic Tom         118:Synth Drum          119:Reverse Cymbal\n";
	cout << "120:Guitar Fret Noise   121:Breath Noise        122:Seashore            123:Bird Tweet\n";
	cout << "124:Telephone Ring      125:Helicopter          126:Applause            127:Gunshot\n\n";
	cout << "Enter new instrument (0-127):\n";
}


int main()
{
	midiout = new RtMidiOut();

	int currentKey = -1;
	bool keyPressed = false;


	unsigned int nPorts = midiout->getPortCount();
	if (nPorts == 0)
	{
		cout << "No ports available!\n";
		goto cleanup;
	}

	midiout->openPort(0);

	initialize();

	printKeyboard();

	while (true)
	{
		keyPressed = false;
		for (int k = 0; k < 21; k++)
		{
			if (GetAsyncKeyState((unsigned char)("ZSXDCVGBHNJM\xbcL\xbe\xba\xbfQUIO"[k])) & 0x8000)
			{
				if (currentKey != k)
				{
					if (k == 17)
					{
						return 0;
					}
					else if (k == 18)
					{
						cout << "Enter new volume (0-127):\n";
						int volume;
						cin >> volume;
						setVolume(volume);
					}
					else if (k == 19)
					{
						printInstruments();
						int instrument;
						cin >> instrument;
						setInstrument(instrument);
					}
					else if (k == 20)
					{
						cout << "Enter new octave (0-9):";
						cin >> octave;
					}
					else
					{
						noteOn((octave * 12) + k);
						currentKey = k;
					}
				}
				keyPressed = true;
			}
		}
		if (!keyPressed)
		{
			if (currentKey != -1)
			{
				noteOff((octave * 12) + currentKey);
				currentKey = -1;
			}
		}
	}

cleanup:
	delete midiout;

	return 0;
}
