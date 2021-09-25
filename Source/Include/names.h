#ifndef names_h
#define names_h

#include <string>
#include <vector>

class NameFactory
{
 public:
  NameFactory();

  std::string getFirstName(unsigned int seed);
  std::string getMaleFirstName(unsigned int seed);
  std::string getFemaleFirstName(unsigned int seed);
  std::string getOtherFirstName(unsigned int seed);
  std::string getLastName(unsigned int seed);

 private:
  std::vector<std::string> m_firstNames;
  std::vector<std::string> m_lastNames;
  std::vector<std::string> m_maleNames;
  std::vector<std::string> m_femaleNames;
  std::vector<std::string> m_otherNames;
};


#endif //names_h
