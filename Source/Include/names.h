#ifndef names_h
#define names_h

#include <string>
#include <vector>

class NameFactory
{
 public:
  NameFactory();

  std::string getMaleFirstName(int wx, int wy, int residentIndex, std::string tag);
  std::string getFemaleFirstName(int wx, int wy, int residentIndex, std::string tag);
  std::string getOtherFirstName(int wx, int wy, int residentIndex, std::string tag);
  std::string getLastName(int wx, int wy, int residentIndex, std::string tag);

 private:
  std::vector<std::string> m_firstNames;
  std::vector<std::string> m_lastNames;
  std::vector<std::string> m_maleNames;
  std::vector<std::string> m_femaleNames;
  std::vector<std::string> m_otherNames;
};


#endif //names_h
