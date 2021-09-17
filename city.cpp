// CITY.CPP

#include "city.h"

#include <cctype>
#include <cstring>
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

  if (val < 75) {
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

  return std::string(nameBuffer);
}
