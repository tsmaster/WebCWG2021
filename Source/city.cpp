// CITY.CPP

#include "city.h"

#include <cctype>
#include <cstring>
#include <map>
#include <vector>

#include "bdg_random.h"

extern std::vector<std::string> CityNames;

City::City(int x, int y)
{
  m_coord = Coord(x, y, 0);
  m_name = makeName();
  m_population = 1234;

  printf("making city %s at %d %d\n", m_name.c_str(), x, y);
}

std::string City::makeName()
{
  unsigned int nameSeed = makeSeedKey(m_coord.x, m_coord.y, 0, "PICK NAME ALGO");
  srand(nameSeed);

  int val = randomrange(0, 100);

  if (val < 90) {
    return makeMarkovName();
  } else if (val < 95) {
    return makeAltName();
  } else {
    int nameCount = CityNames.size();
    int nameIndex = randomrange(0, nameCount);
    return CityNames[nameIndex];
  }
}

std::string City::makeAltName()
{
  unsigned int nameSeed = makeSeedKey(m_coord.x, m_coord.y, 0, "CITY NAME");
  srand(nameSeed);

  char* nameBuffer = (char*)calloc(20, 1);

  int nameLen = randomrange(4,10);

  std::string vowels = std::string("aeiou");
  std::string consonants = std::string("bcdfghjklmnprstvwxyz");
  std::string allLetters = vowels + consonants;

  char* s = nameBuffer;
  while (strlen(nameBuffer) < nameLen) {
    if (strlen(nameBuffer) == 0) {
      *s = allLetters[randomrange(0, allLetters.length())];
    } else {
      char prevChar = *(s-1);

      size_t charIndexInVowels = vowels.find(prevChar);

      if (charIndexInVowels != std::string::npos) {
	// prev was vowel, append a consonant
	*s = consonants[randomrange(0, consonants.length())];
      } else {
	// prev was consonant, append a vowel
	*s = vowels[randomrange(0, vowels.length())];
      }
    }
    ++s;
  }

  nameBuffer[0] = toupper(nameBuffer[0]);

  std::string outName = std::string(nameBuffer);
  free(nameBuffer);

  return outName;
}

std::string City::makeMarkovName()
{
  unsigned int nameSeed = makeSeedKey(m_coord.x, m_coord.y, 0, "MARKOV CITY NAME");
  srand(nameSeed);
  
  std::map<char, std::string> markov = {
    {'a', "n$rlm"},
    {'b', "aueoi"},
    {'c', "haioe"},
    {'d', "a$eoi"},
    {'e', "$nrls"},
    {'f', "aoure"},
    {'g', "$auoe"},
    {'h', "aouei"},
    {'i', "n$als"},
    {'j', "iauoe"},
    {'k', "a$oui"},
    {'l', "aeilo"},
    {'m', "aeo$i"},
    {'n', "g$adt"},
    {'o', "n$url"},
    {'p', "aouei"},
    {'q', "iuaq$"},
    {'r', "a$ieo"},
    {'s', "ha$ti"},
    {'t', "ao$ei"},
    {'u', "$ranl"},
    {'v', "iaeo$"},
    {'w', "aeuo$"},
    {'x', "ia$uv"},
    {'y', "a$uio"},
    {'z', "ha$iu"},
  };

  int MAX_LEN = 12;
  int MIN_LEN = 4;
  
  char* nameBuffer = (char*) calloc(MAX_LEN, 1);

  char startingLetter = 'a' + randomrange(0, 25);

  nameBuffer[0] = startingLetter;

  int i = 1;

  while (i < MAX_LEN - 1) {
    char prevLetter = nameBuffer[i-1];
    std::string nexts = markov[prevLetter];
    char thisLetter = nexts[randomrange(0,5)];
    if (thisLetter == '$') {
      if (i>= MIN_LEN) {
	break;
      } else {
	continue;
      }
    }
    nameBuffer[i] = thisLetter;
    ++i;
  }

  nameBuffer[0] = toupper(nameBuffer[0]);
  std::string outName = std::string(nameBuffer);
  free(nameBuffer);
  return outName;
}
