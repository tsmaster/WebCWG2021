#include "person.h"


#include "bdg_random.h"
#include "names.h"

void Person::generateName(int wx, int wy, int personIndex)
{
  srand(makeSeedKey(wx, wy, personIndex, "GENDER ROLL"));

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
    generateMaleName(wx, wy, personIndex);
    break;
  case Gender::Female:
    generateFemaleName(wx, wy, personIndex);
    break;
  case Gender::Other:
    generateOtherName(wx, wy, personIndex);
    break;
  }
}

void Person::generateMaleName(int wx, int wy, int personIndex)
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
    std::string firstname = nf.getMaleFirstName(wx, wy, personIndex, std::string("MFN"));
    std::string lastname = nf.getLastName(wx, wy, personIndex, std::string("MLN"));
    m_names.push_back(firstname);
    m_names.push_back(lastname);
    m_preferredName = firstname + std::string(" ") + lastname;
  } else if (roll < 77) {
    // first, mi, last
    std::string firstname = nf.getMaleFirstName(wx, wy, personIndex, std::string("MFN"));
    std::string middlename = nf.getMaleFirstName(wx, wy, personIndex, std::string("MMN"));
    std::string lastname = nf.getLastName(wx, wy, personIndex, std::string("MLN"));
    m_names.push_back(firstname);
    m_names.push_back(middlename);
    m_names.push_back(lastname);
    m_preferredName = firstname + std::string(" ") + middlename.substr(0,1) + std::string(". ") + lastname;
  } else if (roll < 87) {
    // first, middle, last
    std::string firstname = nf.getMaleFirstName(wx, wy, personIndex, std::string("MFN"));
    std::string middlename = nf.getMaleFirstName(wx, wy, personIndex, std::string("MMN"));
    std::string lastname = nf.getLastName(wx, wy, personIndex, std::string("MLN"));
    m_names.push_back(firstname);
    m_names.push_back(middlename);
    m_names.push_back(lastname);
    m_preferredName = firstname + std::string(" ") + middlename + std::string(" ") + lastname;
  } else if (roll < 95) {
    // fi, mi, last
    std::string firstname = nf.getMaleFirstName(wx, wy, personIndex, std::string("MFN"));
    std::string middlename = nf.getMaleFirstName(wx, wy, personIndex, std::string("MMN"));
    std::string lastname = nf.getLastName(wx, wy, personIndex, std::string("MLN"));
    m_names.push_back(firstname);
    m_names.push_back(middlename);
    m_names.push_back(lastname);
    m_preferredName = firstname.substr(0,1) + std::string(". ") + middlename.substr(0,1) + std::string(". ") + lastname;
  } else {
    // fi, middle, last
    std::string firstname = nf.getMaleFirstName(wx, wy, personIndex, std::string("MFN"));
    std::string middlename = nf.getMaleFirstName(wx, wy, personIndex, std::string("MMN"));
    std::string lastname = nf.getLastName(wx, wy, personIndex, std::string("MLN"));
    m_names.push_back(firstname);
    m_names.push_back(middlename);
    m_names.push_back(lastname);
    m_preferredName = firstname.substr(0,1) + std::string(". ") + middlename + std::string(" ") + lastname;
  }    
}

void Person::generateFemaleName(int wx, int wy, int personIndex)
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
    std::string firstname = nf.getFemaleFirstName(wx, wy, personIndex, std::string("FFN"));
    std::string lastname = nf.getLastName(wx, wy, personIndex, std::string("FLN"));
    m_names.push_back(firstname);
    m_names.push_back(lastname);
    m_preferredName = firstname + std::string(" ") + lastname;
  } else if (roll < 85) {
    // first, last-last2
    std::string firstname = nf.getFemaleFirstName(wx, wy, personIndex, std::string("FLN"));
    std::string lastname = nf.getLastName(wx, wy, personIndex, std::string("FLN"));
    std::string lastname2 = nf.getLastName(wx, wx, personIndex, std::string("FLN2"));
    m_names.push_back(firstname);
    m_names.push_back(lastname);
    m_names.push_back(lastname2);
    m_preferredName = firstname + std::string(" ") + lastname + std::string("-") + lastname2;
  } else if (roll < 90) {
    // first, mi, last
    std::string firstname = nf.getFemaleFirstName(wx, wy, personIndex, std::string("FFN"));
    std::string middlename = nf.getFemaleFirstName(wx, wy, personIndex, std::string("FMN"));
    std::string lastname = nf.getLastName(wx, wy, personIndex, std::string("FLN"));
    m_names.push_back(firstname);
    m_names.push_back(middlename);
    m_names.push_back(lastname);
    m_preferredName = firstname + std::string(" ") + middlename.substr(0,1) + std::string(". ") + lastname;
  } else if (roll < 95) {
    // fi, middle, last
    std::string firstname = nf.getFemaleFirstName(wx, wy, personIndex, std::string("FFN"));
    std::string middlename = nf.getFemaleFirstName(wx, wy, personIndex, std::string("FMN"));
    std::string lastname = nf.getLastName(wx, wy, personIndex, std::string("FLN"));
    m_names.push_back(firstname);
    m_names.push_back(middlename);
    m_names.push_back(lastname);
    m_preferredName = firstname.substr(0,1) + std::string(". ") + middlename + std::string(" ") + lastname;
  } else {
    // fi, mi, last
    std::string firstname = nf.getFemaleFirstName(wx, wy, personIndex, std::string("FFN"));
    std::string middlename = nf.getFemaleFirstName(wx, wy, personIndex, std::string("FMN"));
    std::string lastname = nf.getLastName(wx, wy, personIndex, std::string("FLN"));
    m_names.push_back(firstname);
    m_names.push_back(middlename);
    m_names.push_back(lastname);
    m_preferredName = firstname.substr(0, 1) + std::string(". ") + middlename.substr(0,1) + std::string(". ") + lastname;
  }  
}

void Person::generateOtherName(int wx, int wy, int personIndex)
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
    std::string firstname = nf.getOtherFirstName(wx, wy, personIndex, std::string("OFN"));
    std::string lastname = nf.getLastName(wx, wy, personIndex, std::string("OLN"));
    m_names.push_back(firstname);
    m_names.push_back(lastname);
    m_preferredName = firstname + std::string(" ") + lastname;
  } else if (roll < 98) {
    // first, middle, last
    std::string firstname = nf.getOtherFirstName(wx, wy, personIndex, std::string("OFN"));
    std::string middlename = nf.getOtherFirstName(wx, wy, personIndex, std::string("OMN"));
    std::string lastname = nf.getLastName(wx, wy, personIndex, std::string("OLN"));
    m_names.push_back(firstname);
    m_names.push_back(middlename);
    m_names.push_back(lastname);
    m_preferredName = firstname + std::string(" ") + middlename + std::string(" ") + lastname;
  } else {
    // first
    std::string firstname = nf.getOtherFirstName(wx, wy, personIndex, std::string("OMono"));
    m_names.push_back(firstname);
    m_preferredName = firstname;
  }  
}
