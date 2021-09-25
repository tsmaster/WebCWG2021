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

  void generateName(unsigned int seed);

 protected:  
  void generateMaleName();
  void generateFemaleName();
  void generateOtherName();
};


#endif //person_h
