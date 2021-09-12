// CITY.CPP

#include "city.h"


City::City(int x, int y)
{
  m_coord = Coord(x, y, 0);
  m_name = makeName();
}

// TODO rewrite name generation

std::string City::makeName()
{
  return std::string("??? City ???");

  /*
        random.seed(seed)

        s = ""
        length = random.randrange(4, 10)

        vowels = "aeiou"
        consonants = "bcdfghjklmnprstvwxyz"
        allletters = vowels+consonants
        
        while len(s) < length:
            if len(s) == 0:
                s = s + random.choice(allletters)
            elif s[-1] in vowels:
                s = s + random.choice(consonants)
            else:
                s = s + random.choice(vowels)
        return s
  */

  
}
