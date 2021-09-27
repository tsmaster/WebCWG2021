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

class PersonAddress {
 public:
  int wx;
  int wy;
  int personIndex;

  PersonAddress(int in_wx, int in_wy, int in_personIndex) {
    wx = in_wx; wy = in_wy; personIndex = in_personIndex;
  }

  bool operator == (const PersonAddress& other) {
    return ((wx == other.wx) &&
	    (wy == other.wy) &&
	    (personIndex == other.personIndex));
  }

  bool isValid() { return personIndex >= 0; }
};

class Person {
 public:
  std::vector<std::string> m_names;

  std::string m_preferredName;

  Gender m_gender;

  void generateName(int wx, int wy, int personIndex);

  void setBuildingIndex(int buildingIndex) { m_buildingIndex = buildingIndex; }
  int getBuildingIndex() { return m_buildingIndex; }

  bool isFriend(PersonAddress& friendAddress);
  void addFriend(PersonAddress friendAddress) { m_friends.push_back(friendAddress); }
  int countFriends() { return m_friends.size(); }
  std::vector<PersonAddress> getFriendAddresses() { return m_friends; }

 protected:  
  void generateMaleName(int wx, int wy, int personIndex);
  void generateFemaleName(int wx, int wy, int personIndex);
  void generateOtherName(int wx, int wy, int personIndex);

 private:
  int m_buildingIndex = -1;

  std::vector<PersonAddress> m_friends;
};


#endif //person_h
