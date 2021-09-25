#ifndef person_h
#define person_h

#include <string>
#include <vector>


enum class Gender {
  GenderNone,
  Male,
  Female,
  Other
};

class Person {
 public:
  std::vector<std::string> m_names;

  std::string m_preferredName;

  Gender m_gender;

  void generateName(int wx, int wy, int personIndex);

 protected:  
  void generateMaleName(int wx, int wy, int personIndex);
  void generateFemaleName(int wx, int wy, int personIndex);
  void generateOtherName(int wx, int wy, int personIndex);
};


#endif //person_h
