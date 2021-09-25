#include "person.h"


#include "bdg_random.h"
#include "names.h"

void Person::generateName(unsigned int seed)
{
  srand(seed);

  int genderRoll = randomrange(0,20);

  if (genderRoll < 9) {
    m_gender = Gender::Male;
  } else if (genderRoll < 18) {
    m_gender = Gender::Female;
  } else {
    m_gender = Gender::Other;
  }

  switch (m_gender) {
  case Gender::Male:
    generateMaleName();
    break;
  case Gender::Female:
    generateFemaleName();
    break;
  case Gender::Other:
    generateOtherName();
    break;
  }
}

void Person::generateMaleName()
{
  NameFactory nf;
  /* Patterns:
     65% first, last
     12% first, mi, last
     10% first, middle, last
     8% fi, mi, last
     5% fi, middle, last
   */

  int roll = randomrange(0, 100);
  if (roll < 65) {
    // first, last
    std::string firstname = nf.getMaleFirstName(makeSeedKey(1, roll, 1024, "MALE FIRST NAME"));
    std::string lastname = nf.getLastName(makeSeedKey(1, roll, 1025, "MALE LAST NAME"));
    m_names.push_back(firstname);
    m_names.push_back(lastname);
    m_preferredName = firstname + std::string(" ") + lastname;
  } else if (roll < 77) {
    // first, mi, last
    std::string firstname = nf.getMaleFirstName(makeSeedKey(1, roll, 1024, "MALE FIRST NAME"));
    std::string middlename = nf.getMaleFirstName(makeSeedKey(1, roll, 1025, "MALE MIDDLE NAME"));
    std::string lastname = nf.getLastName(makeSeedKey(1, roll, 1026, "MALE LAST NAME"));
    m_names.push_back(firstname);
    m_names.push_back(middlename);
    m_names.push_back(lastname);
    m_preferredName = firstname + std::string(" ") + middlename.substr(0,1) + std::string(". ") + lastname;
  } else if (roll < 87) {
    // first, middle, last
    std::string firstname = nf.getMaleFirstName(makeSeedKey(1, roll, 1024, "MALE FIRST NAME"));
    std::string middlename = nf.getMaleFirstName(makeSeedKey(1, roll, 1025, "MALE MIDDLE NAME"));
    std::string lastname = nf.getLastName(makeSeedKey(1, roll, 1026, "MALE LAST NAME"));
    m_names.push_back(firstname);
    m_names.push_back(middlename);
    m_names.push_back(lastname);
    m_preferredName = firstname + std::string(" ") + middlename + std::string(" ") + lastname;
  } else if (roll < 95) {
    // fi, mi, last
    std::string firstname = nf.getMaleFirstName(makeSeedKey(1, roll, 1024, "MALE FIRST NAME"));
    std::string middlename = nf.getMaleFirstName(makeSeedKey(1, roll, 1025, "MALE MIDDLE NAME"));
    std::string lastname = nf.getLastName(makeSeedKey(1, roll, 1026, "MALE LAST NAME"));
    m_names.push_back(firstname);
    m_names.push_back(middlename);
    m_names.push_back(lastname);
    m_preferredName = firstname.substr(0,1) + std::string(". ") + middlename.substr(0,1) + std::string(". ") + lastname;
  } else {
    // fi, middle, last
    std::string firstname = nf.getMaleFirstName(makeSeedKey(1, roll, 1024, "MALE FIRST NAME"));
    std::string middlename = nf.getMaleFirstName(makeSeedKey(1, roll, 1025, "MALE MIDDLE NAME"));
    std::string lastname = nf.getLastName(makeSeedKey(1, roll, 1026, "MALE LAST NAME"));
    m_names.push_back(firstname);
    m_names.push_back(middlename);
    m_names.push_back(lastname);
    m_preferredName = firstname.substr(0,1) + std::string(". ") + middlename + std::string(" ") + lastname;
  }    
}

void Person::generateFemaleName()
{
  NameFactory nf;
  /* Patterns:
     75% first, last
     10% first, last-last2
     5% first, mi, last
     5% fi, middle, last
     5% fi, mi, last
   */

  int roll = randomrange(0, 100);
  if (roll < 75) {
    // first, last
    std::string firstname = nf.getFemaleFirstName(makeSeedKey(2, roll, 8000, "FEMALE FIRST NAME"));
    std::string lastname = nf.getLastName(makeSeedKey(1, roll, 8001, "FEMALE LAST NAME"));
    m_names.push_back(firstname);
    m_names.push_back(lastname);
    m_preferredName = firstname + std::string(" ") + lastname;
  } else if (roll < 85) {
    // first, last-last2
    std::string firstname = nf.getFemaleFirstName(makeSeedKey(2, roll, 8000, "FEMALE FIRST NAME"));
    std::string lastname = nf.getLastName(makeSeedKey(2, roll, 8001, "FEMALE LAST NAME"));
    std::string lastname2 = nf.getLastName(makeSeedKey(2, roll, 8002, "FEMALE LAST NAME 2"));
    m_names.push_back(firstname);
    m_names.push_back(lastname);
    m_names.push_back(lastname2);
    m_preferredName = firstname + std::string(" ") + lastname + std::string("-") + lastname2;
  } else if (roll < 90) {
    // first, mi, last
    std::string firstname = nf.getFemaleFirstName(makeSeedKey(2, roll, 8000, "FEMALE FIRST NAME"));
    std::string middlename = nf.getFemaleFirstName(makeSeedKey(2, roll, 8001, "FEMALE MIDDLE NAME"));
    std::string lastname = nf.getLastName(makeSeedKey(2, roll, 8002, "FEMALE LAST NAME"));
    m_names.push_back(firstname);
    m_names.push_back(middlename);
    m_names.push_back(lastname);
    m_preferredName = firstname + std::string(" ") + middlename.substr(0,1) + std::string(". ") + lastname;
  } else if (roll < 95) {
    // fi, middle, last
    std::string firstname = nf.getFemaleFirstName(makeSeedKey(2, roll, 8000, "FEMALE FIRST NAME"));
    std::string middlename = nf.getFemaleFirstName(makeSeedKey(2, roll, 8001, "FEMALE MIDDLE NAME"));
    std::string lastname = nf.getLastName(makeSeedKey(2, roll, 8002, "FEMALE LAST NAME"));
    m_names.push_back(firstname);
    m_names.push_back(middlename);
    m_names.push_back(lastname);
    m_preferredName = firstname.substr(0,1) + std::string(". ") + middlename + std::string(" ") + lastname;
  } else {
    // fi, mi, last
    std::string firstname = nf.getFemaleFirstName(makeSeedKey(2, roll, 8000, "FEMALE FIRST NAME"));
    std::string middlename = nf.getFemaleFirstName(makeSeedKey(2, roll, 8001, "FEMALE MIDDLE NAME"));
    std::string lastname = nf.getLastName(makeSeedKey(2, roll, 8002, "FEMALE LAST NAME"));
    m_names.push_back(firstname);
    m_names.push_back(middlename);
    m_names.push_back(lastname);
    m_preferredName = firstname.substr(0, 1) + std::string(". ") + middlename.substr(0,1) + std::string(". ") + lastname;
  }  
}

void Person::generateOtherName()
{
  NameFactory nf;
  /* Patterns:
     90% first, last
     9%  first, middle, last
     1% first
   */

  int roll = randomrange(0, 100);
  if (roll < 90) {
    // first, last
    std::string firstname = nf.getOtherFirstName(makeSeedKey(3, roll, 9000, "OTHER FIRST NAME"));
    std::string lastname = nf.getLastName(makeSeedKey(3, roll, 9001, "OTHER LAST NAME"));
    m_names.push_back(firstname);
    m_names.push_back(lastname);
    m_preferredName = firstname + std::string(" ") + lastname;
  } else if (roll < 98) {
    // first, middle, last
    std::string firstname = nf.getOtherFirstName(makeSeedKey(3, roll, 9000, "OTHER FIRST NAME"));
    std::string middlename = nf.getOtherFirstName(makeSeedKey(3, roll, 9001, "OTHER MIDDLE NAME"));
    std::string lastname = nf.getLastName(makeSeedKey(3, roll, 9002, "OTHER LAST NAME"));
    m_names.push_back(firstname);
    m_names.push_back(middlename);
    m_names.push_back(lastname);
    m_preferredName = firstname + std::string(" ") + middlename + std::string(" ") + lastname;
  } else {
    // first
    std::string firstname = nf.getOtherFirstName(makeSeedKey(3, roll, 9000, "OTHER MONONYM"));
    m_names.push_back(firstname);
    m_preferredName = firstname;
  }  
}
