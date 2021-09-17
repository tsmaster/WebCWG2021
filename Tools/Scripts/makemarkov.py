import string

city_names = [
  "New York City",
  "Los Angeles",
  "Chicago",
  "Houston",
  "Phoenix",
  "Philadelphia",
  "San Antonio",
  "San Diego",
  "Dallas",
  "Austin",
  "San Jose",
  "Fort Worth",
  "Jacksonville",
  "Columbus",
  "Charlotte",
  "Indianapolis",
  "San Francisco",
  "Seattle",
  "Denver",
  "Washington",
  "Boston",
  "El Paso",
  "Nashville",
  "Oklahoma City",
  "Las Vegas",
  "Detroit",
  "Portland",
  "Memphis",
  "Louisville",
  "Milwaukee",
  "Baltimore",
  "Albuquerque",
  "Tucson",
  "Mesa",
  "Fresno",
  "Sacramento",
  "Atlanta",
  "Kansas City",
  "Colorado Springs",
  "Raleigh",
  "Omaha",
  "Miami",
  "Long Beach",
  "Virginia Beach",
  "Oakland",
  "Minneapolis",
  "Tampa",
  "Tulsa",
  "Arlington",
  "Wichita",
  "Bakersfield",
  "Aurora",
  "New Orleans",
  "Cleveland",
  "Anaheim",
  "Henderson",
  "Honolulu",
  "Riverside",
  "Santa Ana",
  "Corpus Christi",
  "Lexington",
  "San Juan",
  "Stockton",
  "St. Paul",
  "Cincinnati",
  "Greensboro",
  "Pittsburgh",
  "Irvine",
  "St. Louis",
  "Lincoln",
  "Orlando",
  "Durham",
  "Plano",
  "Anchorage",
  "Newark",
  "Chula Vista",
  "Fort Wayne",
  "Chandler",
  "Toledo",
  "St. Petersburg",
  "Reno",
  "Laredo",
  "Scottsdale",
  "North Las Vegas",
  "Lubbock",
  "Madison",
  "Gilbert",
  "Jersey City",
  "Glendale",
  "Buffalo",
  "Winston-Salem",
  "Chesapeake",
  "Fremont",
  "Norfolk",
  "Irving",
  "Garland",
  "Paradise",
  "Arlington",
  "Richmond",
  "Hialeah",
  "Boise",
  "Spokane",
  "Frisco",
  "Moreno Valley",
  "Tacoma",
  "Fontana",
  "Modesto",
  "Baton Rouge",
  "Port St. Lucie",
  "San Bernardino",
  "McKinney",
  "Fayetteville",
  "Santa Clarita",
  "Des Moines",
  "Oxnard",
  "Birmingham",
  "Spring Valley",
  "Huntsville",
  "Rochester",
  "Cape Coral",
  "Tempe",
  "Grand Rapids",
  "Yonkers",
  "Overland Park",
  "Salt Lake City",
  "Amarillo",
  "Augusta",
  "Columbus",
  "Tallahassee",
  "Montgomery",
  "Huntington Beach",
  "Akron",
  "Little Rock",
  "Glendale",
  "Grand Prairie",
  "Aurora",
  "Sunrise Manor",
  "Ontario",
  "Sioux Falls",
  "Knoxville",
  "Vancouver",
  "Mobile",
  "Worcester",
  "Chattanooga",
  "Brownsville",
  "Peoria",
  "Fort Lauderdale",
  "Shreveport",
  "Newport News",
  "Providence",
  "Elk Grove",
  "Rancho Cucamonga",
  "Salem",
  "Pembroke Pines",
  "Santa Rosa",
  "Eugene",
  "Oceanside",
  "Cary",
  "Fort Collins",
  "Corona",
  "Enterprise",
  "Garden Grove",
  "Springfield",
  "Clarksville",
  "Bayamon",
  "Lakewood",
  "Alexandria",
  "Hayward",
  "Murfreesboro",
  "Killeen",
  "Hollywood",
  "Lancaster",
  "Salinas",
  "Jackson",
  "Midland",
  "Macon County",
  "Kansas City",
  "Palmdale",
  "Sunnyvale",
  "Springfield",
  "Escondido",
  "Pomona",
  "Bellevue",
  "Surprise",
  "Naperville",
  "Pasadena",
  "Denton",
  "Roseville",
  "Joliet",
  "Thornton",
  "McAllen",
  "Paterson",
  "Rockford",
  "Carrollton",
  "Bridgeport",
  "Miramar",
  "Round Rock",
  "Metairie",
  "Olathe",
  "Waco",
  "Tokyo",
  "Delhi",
  "Shanghai",
  "Sao Paulo",
  "Mexico City",
  "Dhaka",
  "Cairo",
  "Beijing",
  "Mumbai",
  "Osaka",
  "Karachi",
  "Chongqing",
  "Istanbul",
  "Buenos Aires",
  "Kolkata",
  "Kinshasa",
  "Lagos",
  "Manila",
  "Tianjin",
  "Guangzhou",
  "Rio De Janeiro",
  "Lahore",
  "Bangalore",
  "Moscow",
  "Shenzhen",
  "Chennai",
  "Bogota",
  "Paris",
  "Jakarta",
  "Lima",
  "Bangkok",
  "Hyderabad",
  "Seoul",
  "Nagoya",
  "London",
  "Chengdu",
  "Tehran",
  "Nanjing",
  "Ho Chi Minh City",
  "Luanda",
  "Wuhan",
  "Xi An Shaanxi",
  "Ahmedabad",
  "New York City",
  "Kuala Lumpur",
  "Hangzhou",
  "Hong Kong",
  "Surat",
  "Dongguan",
  "Suzhou",
  "Foshan",
  "Riyadh",
  "Shenyang",
  "Baghdad",
  "Dar Es Salaam",
  "Santiago",
  "Pune",
  "Madrid",
  "Haerbin",
  "Toronto",
  "Belo Horizonte",
  "Singapore",
  "Khartoum",
  "Johannesburg",
  "Dalian",
  "Qingdao",
  "Barcelona",
  "Fukuoka",
  "Ji Nan Shandong",
  "Zhengzhou",
  "Saint Petersburg",
  "Yangon",
  "Alexandria",
  "Abidjan",
  "Guadalajara",
  "Ankara",
  "Chittagong",
  "Melbourne",
  "Addis Ababa",
  "Sydney",
  "Monterrey",
  "Nairobi",
  "Hanoi",
  "Brasilia",
  "Cape Town",
  "Jiddah",
  "Changsha",
  "Kunming",
  "Urumqi",
  "Changchun",
  "Xinbei",
  "Shantou",
  "Hefei",
  "Kabul",
  "Rome",
  "Ningbo",
  "Tel Aviv",
  "Montreal",
  "Shijiazhuang",
  "Recife",
  "Yaounde",
  "Porto Alegre",
  "Fortaleza",
  "Kano",
  "Medellin",
  "Jaipur",
  "Los Angeles",
  "Taiyuan Shanxi",
  "Nanning",
  "Ekurhuleni",
  "Salvador",
  "Casablanca",
  "Douala",
  "Xiamen",
  "Lucknow",
  "Fuzhou Fujian",
  "Changzhou",
  "Kozhikode",
  "Curitiba",
  "Wenzhou",
  "Nanchang",
  "Ibadan",
  "Malappuram",
  "Berlin",
  "Tangshan Hebei",
  "Faisalabad",
  "Antananarivo",
  "Bekasi",
  "Kumasi",
  "Kampala",
  "Busan",
  "Abuja",
  "Guiyang",
  "Asuncion",
  "Santo Domingo",
  "Campinas",
  "Wuxi",
  "Mashhad",
  "Puebla",
  "Dakar",
  "Thrissur",
  "Kochi",
  "Kuwait City",
  "Durban",
  "Port Harcourt",
  "Lanzhou",
  "Kanpur",
  "Athens",
  "Milan",
  "Indore",
  "Pyongyang",
  "Sanaa",
  "Guayaquil",
  "Izmir",
  "Kiev",
  "Guatemala City",
  "Surabaya",
  "Lisbon",
  "Caracas",
  "Zhongshan",
  "Nagpur",
  "Shizuoka",
  "Dubai",
  "Ouagadougou",
  "Lusaka",
  "Coimbatore",
  "Port Au Prince",
  "Depok",
  "Handan",
  "Incheon",
  "Cali",
  "Algiers",
  "Huaian",
  "Manchester",
  "Goiania",
  "Weifang",
  "Taibei",
  "Bamako",
  "Thiruvananthapuram",
  "Zibo",
  "Chicago",
  "Sapporo",
  "Pretoria",
  "Mbuji Mayi",
  "Shaoxing",
  "Birmingham",
  "Yantai",
  "Bandung",
  "Vancouver",
  "Huizhou",
  "Lubumbashi",
  "Accra",
  "Tashkent",
  "Toluca De Lerdo",
  "Patna",
  "Brazzaville",
  "Luoyang",
  "Bhopal",
  "San Juan",
  "Damascus",
  "Brisbane",
  "Beirut",
  "Tunis",
  "Tangerang",
  "Mogadishu",
  "Baku",
  "Medan",
  "Belem",
  "Nantong",
  "Sendai",
  "Houston",
  "Manaus",
  "Barranquilla",
  "Maracaibo",
  "Gujranwala",
  "Rawalpindi",
  "Peshawar",
  "Taoyuan",
  "Agra",
  "Hohhot",
  "Baotou",
  "Vadodara",
  "Kannur",
  "Liuzhou",
  "Visakhapatnam",
  "Xuzhou",
  "Daegu",
  "Naples",
  "Amman",
  "Tijuana",
  "Esfahan",
  "Phnom Penh",
  "Havana",
  "Nashik",
  "Grande Vitoria",
  "Vijayawada",
  "Brussels",
  "Mecca",
  "Hiroshima",
  "Perth",
  "Multan",
  "Yangzhou",
  "Minsk",
  "Bursa",
  "Baoding",
  "Aleppo",
  "Putian",
  "Taizhou Zhejiang",
  "Conakry",
  "Linyi Shandong",
  "Wuhu Anhui",
  "Vienna",
  "Kollam",
  "Valencia",
  "Rajkot",
  "Haikou",
  "Almaty",
  "Baixada Santista",
  "Yancheng Jiangsu",
  "Daqing",
  "Rabat",
  "West Yorkshire",
  "Semarang",
  "Quito",
  "Panama City",
  "Hyderabad",
  "Ludhiana",
  "La Paz",
  "Lianyungang",
  "Lome",
  "Davao City",
  "Leon De Los Aldamas",
  "Zhuhai",
  "Turin",
  "Bucharest",
  "Adana",
  "Warsaw",
  "Hamburg",
  "Datong",
  "Benin City",
  "Budapest",
  "Madurai",
  "Montevideo",
  "Quanzhou",
  "Palembang",
  "Santa Cruz",
  "Matola",
  "Gaziantep",
  "Sharjah",
  "Phoenix",
  "Lyon",
  "Meerut",
  "Jiangmen",
  "Can Tho",
  "Raipur",
  "Varanasi",
  "Xiangyang",
  "Mosul",
  "Glasgow",
  "Novosibirsk",
  "Shiraz",
  "La Laguna",
  "Cixi",
  "Stockholm",
  "Anshan",
  "Auckland",
  "Jamshedpur",
  "Tabriz",
  "Yinchuan",
  "Jilin",
  "Srinagar",
  "Batam",
  "Ulaanbaatar",
  "Marseille",
  "Makassar",
  "Yichang",
  "Aurangabad",
  "Muscat",
  "Qinhuangdao",
  "Philadelphia",
  "Cordoba",
  "Qiqihaer",
  "Xining",
  "Karaj",
  "San Antonio",
  "Calgary",
  "Hengyang",
  "Daejon",
  "Monrovia",
  "Tiruppur",
  "Rosario",
  "Munich",
  "Gaoxiong",
  "Harare",
  "Ciudad Juarez",
  "Anyang",
  "Kananga",
  "Gwangju",
  "Suqian",
  "Jining Shandong",
  "Medina",
  "Yekaterinburg",
  "Abu Dhabi",
  "Jodhpur",
  "Grande Sao Luis",
  "Edmonton",
  "Natal",
  "Tegucigalpa",
  "Onitsha",
  "N Djamena",
  "Ranchi",
  "Kathmandu",
  "Jabalpur",
  "Mandalay",
  "Zhangjiakou",
  "Huainan",
  "Asansol",
  "Chaozhou",
  "Kota",
  "San Diego",
  "Kharkiv",
  "San Jose",
  "Chon Buri",
  "Allahabad",
  "Gwalior",
  "Ottawa",
  "Zurich",
  "Belgrade",
  "Amritsar",
  "Joao Pessoa",
  "Yiwu",
  "Basra",
  "Taizhou Jiangsu",
  "Nouakchott",
  "Queretaro",
  "Taian Shandong",
  "Homs",
  "Copenhagen",
  "Konya",
  "Bucaramanga",
  "Dhanbad",
  "Weihai",
  "Dallas",
  "Ganzhou",
  "Adelaide",
  "Hai Phong",
  "Mombasa",
  "Taizhong",
  "Maceio",
  "Cochabamba",
  "Niamey",
  "Suweon",
  "Samut Prakan",
  "Joinville",
  "Jiaxing",
  "Kaifeng",
  "Helsinki",
  "Porto",
  "Zhanjiang",
  "Zunyi",
  "Rizhao",
  "Kisangani",
  "Prague",
  "Dongying",
  "Qom",
  "Mianyang Sichuan",
  "Nanchong",
  "Fushun Liaoning",
  "Antalya",
  "Bareilly",
  "Sofia",
  "Shiyan",
  "Kazan",
  "Ad Dammam",
  "Port Elizabeth",
  "Ahvaz",
  "Liuan",
  "Florianopolis",
  "Nizhniy Novgorod",
  "Pointe Noire",
  "Yingkou",
  "Fes",
  "Aligarh",
  "Liuyang",
  "Dublin",
  "Maoming",
  "Tanger",
  "Pekan Baru",
  "Tengzhou",
  "Freetown",
  "San Luis Potosi",
  "Mysore",
  "Chelyabinsk",
  "Moradabad",
  "Barquisimeto",
  "Durg Bhilainagar",
  "Suzhou",
  "Maracay",
  "Astana",
  "Zhuzhou",
  "Ruian",
  "Uyo",
  "Zhenjiang Jiangsu",
  "Baoji",
  "Jieyang",
  "Chifeng",
  "Bhubaneswar",
  "Pingdingshan Henan",
  "Puning",
  "Mendoza",
  "Bogor",
  "Chiang Mai",
  "Mwanza",
  "Tiruchirappalli",
  "Omsk",
  "Merida",
  "Benxi",
  "Huaibei",
  "Lilongwe",
  "Nanyang Henan",
  "Jinhua",
  "Xiangtan Hunan",
  "Kigali",
  "Tripoli",
  "Chandigarh",
  "Jinzhou",
  "Islamabad",
  "Samara",
  "Amsterdam",
  "Da Nang",
  "Haifa",
  "Guilin",
  "Krasnoyarsk",
  "Mexicali",
  "Ufa",
  "Rostov On Don",
  "Hubli Dharwad",
  "Guwahati",
  "Kaduna",
  "Bukavu",
  "Liupanshui",
  "Quetta",
  "Cologne",
  "Aguascalientes",
  "Binzhou",
  "Salem",
  "Abomey Calavi",
  "Maputo",
  "Bandar Lampung",
  "Aba",
  "Pizhou",
  "Nnewi",
  "Tasikmalaya",
  "San Salvador",
  "Yongin",
  "Zaozhuang",
  "Xinxiang",
  "Yueqing",
  "Luohe",
  "Saharanpur",
  "Shimkent",
  "Cuernavaca",
  "Yerevan",
  "Goyang",
  "Tbilisi",
  "Chihuahua",
  "Panjin",
  "Perm",
  "Bujumbura",
  "Jalandhar",
  "Managua",
  "Voronezh",
  "Cartagena",
  "Wenling",
  "Lille",
  "Fuyang",
  "Bishkek",
  "Diyarbakir",
  "Bazhong",
  "Siliguri",
  "Oslo",
  "Shangrao",
  "Changwon",
  "Jingzhou Hubei",
  "Ma'anshan",
  "Zhaoqing",
  "Antwerp",
  "Kermanshah",
  "Xiongan",
  "Bien Hoa",
  "Johor Bahru",
  "Solapur",
  "Samarinda",
  "Toulouse",
  "Mersin",
  "Hargeysa",
  "Teresina",
  "Kirkuk",
  "Fuzhou Jiangxi",
  "Aracaju",
  "Bobo Dioulasso",
  "Leshan",
  "Yueyang",
  "Dezhou",
  "Marrakech",
  "Tampico",
  "Huzhou",
  "Rotterdam",
  "Aden",
  "Austin",
  "San Jose",
  "Denpasar",
  "Odesa",
  "Chenzhou",
  "Xuchang",
  "Volgograd",
  "Saltillo",
  "San Miguel De Tucuman",
  "Asmara",
  "Padang",
  "Cebu City",
  "Acapulco De Juarez",
  "Valparaiso",
  "Sekondi Takoradi",
  "Ikorodu",
  "Kayseri",
  "Warangal",
  "Changshu",
  "Bordeaux",
  "Songkhla",
  "Qujing",
  "Nonthaburi",
  "Yichun Jiangxi",
  "Krasnodar",
  "Ilorin",
  "Cancun",
  "Tshikapa",
  "Nyala",
  "Xintai",
  "Jixi Heilongjiang",
  "Blantyre Limbe",
  "Morelia",
  "Pingxiang Jiangxi",
  "Dnipro",
  "Khulna",
  "Jerusalem",
  "Cucuta",
  "Nice",
  "Dehradun",
  "Seongnam",
  "Fort Worth",
  "Agadir",
  "Mudanjiang",
  "Hamah",
  "Dushanbe",
  "Guiping",
  "Jiujiang",
  "Southampton",
  "Laiwu",
  "Arequipa",
  "Ciudad Guayana",
  "Zamboanga City",
  "Veracruz",
  "Jacksonville",
  "San Pedro Sula",
  "Zhucheng",
  "Pathum Thani",
  "Rajshahi",
  "Chengde",
  "Misratah",
  "Guigang",
  "Jos",
  "Reynosa",
  "Bengbu",
  "Columbus",
  "Villahermosa",
  "Yangjiang",
  "Charlotte",
  "Ulsan",
  "Bangui",
  "Oran",
  "West Rand",
  "Owerri",
  "Campo Grande",
  "Liverpool",
  "Antipolo",
  "Najaf",
  "Zhangzhou",
  "Bergamo",
  "Donetsk",
  "Tianmen",
  "Warri",
  "Londrina",
  "Leiyang",
  "Malang",
  "La Plata",
  "Concepcion",
  "Hengshui",
  "Linfen",
  "Xinyu",
  "Sylhet",
  "Dandong",
  "Indianapolis",
  "Nampula",
  "Deyang",
  "Hermosillo",
  "San Francisco",
  "Trujillo",
  "Taiz",
  "Guntur",
  "Jiangyin",
  "Bhiwandi",
  "Lubango",
  "Liaoyang",
  "Bahawalpur",
  "Changzhi",
  "Tyumen",
  "Soshanguve",
  "Tuxtla Gutierrez",
  "Ashgabat",
  "Erbil",
  "Baishan",
  "Liling",
  "Tainan",
  "Puducherry",
  "Culiacan",
  "Changde",
  "Fuxin",
  "Palermo",
  "Shangqiu",
  "Xingtai",
  "Hufuf Mubarraz",
  "Firozabad",
  "Libreville",
  "Huangshi",
  "Saratov",
  "Banghazi",
  "Valencia",
  "Luzhou",
  "Quebec City",
  "Yibin",
  "Bucheon",
  "Ipoh",
  "Winnipeg",
  "Bogra",
  "Cabinda",
  "Umuahia",
  "Xinyang",
  "Xinghua",
  "Newcastle Upon Tyne",
  "Yangquan",
  "Thessaloniki",
  "Yongzhou",
  "Bologna",
  "Orumiyeh",
  "Xiaogan",
  "Heze",
  "Barcelona Puerto La Cruz",
  "Maiduguri",
  "Kuerle",
  "Niigata",
  "Eskisehir",
  "Cherthala",
  "Quzhou",
  "Zhuji",
  "Sorocaba",
  "Haicheng",
  "Enugu",
  "Nottingham",
  "Tianshui",
  "Huludao",
  "Xalapa",
  "Bikaner",
  "Frankfurt",
  "Huaihua",
  "Nakhon Ratchasima",
  "Vereeniging",
  "Liaocheng",
  "Seattle",
  "Jiaozuo",
  "Bozhou",
  "Nellore",
  "Hamilton",
  "Gebze",
  "Taixing",
  "Cagayan De Oro City",
  "Krakow",
  "Kunshan",
  "Shaoguan",
  "Gorakhpur",
  "Dasmarinas",
  "Amravati",
  "Jincheng",
  "Langfang",
  "Ansan",
  "Ar Rayyan",
  "Sulaimaniya",
  "Cuttack",
  "Bur Sa'id",
  "Denver",
  "Meishan",
  "Zhumadian",
  "Zigong",
  "Benguela",
  "Gaomi",
  "Anqing",
  "Qingyuan",
  "Banjarmasin",
  "Hanchuan",
  "Danyang",
  "Muzaffarnagar",
  "Lokoja",
  "Kumamoto",
  "Kottayam",
  "Belgaum",
  "Zarqa",
  "Zaria",
  "Sheffield",
  "Zanzibar",
  "Gaza",
  "Zaragoza",
  "Linhai",
  "Zaporizhzhya",
  "Malegaon",
  "Sao Jose Dos Campos",
  "Oshogbo",
  "Erduosi Ordoss",
  "Shaoyang",
  "Kayamkulam",
  "Jiamusi",
  "Mangalore",
  "Okayama",
  "Ribeirao Preto",
  "Xianyang Shaanxi",
  "Bunia",
  "Lviv",
  "Rasht",
  "Anqiu",
  "Tongliao",
  "Cheongju",
  "Sialkot",
  "Maturin",
  "Buffalo City",
  "Panzhihua",
  "Suining Sichuan",
  "Yanji",
  "Tongling",
  "Wuzhou",
  "Oaxaca De Juarez",
  "Washington",
  "Sargodha",
  "Bhavnagar",
  "Gold Coast",
  "Yan'an",
  "Kitwe",
  "Florence",
  "Jammu",
  "Yulin Shaanxi",
  "Nanded Waghala",
  "Dazhou",
  "Tirupati",
  "Bacoor",
  "Malanje",
  "Dengzhou",
  "The Hague",
  "Longyan",
  "Yuncheng",
  "Seville",
  "Cotonou",
  "Dongtai",
  "Tolyatti",
  "Salta",
  "Merca",
  "Bali",
  "Yuyao",
  "Boston",
  "Uberlandia",
  "Taif",
  "Yuxi",
  "Vientiane",
  "Bristol",
  "Akure",
  "Ibb",
  "Celaya",
  "Al Hudaydah",
  "Cheonan",
  "Jundiai",
  "Gulbarga",
  "Huambo",
  "Padova",
  "Durgapur",
  "Kurnool",
  "El Paso",
  "Nantes",
  "Buraydah",
  "Zagreb",
  "Zhangjiagang",
  "Pontianak",
  "Amara",
  "Liege",
  "Taicang",
  "Nashville",
  "Genoa",
  "Ezhou",
  "Santiago",
  "Mar Del Plata",
  "Tamale",
  "Zhoukou",
  "Lodz",
  "Goma",
  "Oklahoma City",
  "Lattakia",
  "Las Vegas",
  "Tabuk",
  "Ankang",
  "General Santos City",
  "Renqiu",
  "Detroit",
  "Manama",
  "Loudi",
  "Jeonju",
  "Bijie",
  "Portland",
  "Sokoto",
  "Qinzhou",
  "Macao",
  "Samsun",
  "Denizli",
  "Zhoushan",
  "Busto Arsizio",
  "Tongxiang",
  "Longhai",
  "Puyang",
  "Hezhou",
  "Jhansi",
  "Neijiang",
  "Izhevsk",
  "Memphis",
  "Jamnagar",
  "As Suways",
  "Erode",
  "Doha",
  "Pachuca De Soto",
  "Haimen",
  "Chongjin",
  "Chiclayo",
  "Wuhai",
  "Hegang",
  "Sanya",
  "Be'er Sheva",
  "Durango",
  "Bokaro Steel City",
  "Wroclaw",
  "Irkutsk",
  "Barnaul",
  "Nay Pyi Taw",
  "Bulawayo",
  "Miluo",
  "Venezia",
  "Jambi",
  "Safaqis",
  "Khabarovsk",
  "Herat",
  "Duesseldorf",
  "Belfast",
  "Nasiriyah",
  "Stuttgart",
  "Verona",
  "Raurkela",
  "Jubayl",
  "Riga",
  "Bandar Abbas",
  "Kolhapur",
  "Bacolod",
  "Seregno",
  "Ulyanovsk",
  "Uvira",
  "Al Ain",
  "Bari",
  "Yulin Guangxi",
  "Ajmer",
  "Kuching",
  "Bissau",
  "Bauchi",
  "Geneva",
  "Enshi",
  "Anshun",
  "Colombo",
  "Sihui",
  "Hanzhong",
  "Ujjain",
  "Gothenburg",
  "Jinzhong",
  "Patiala",
  "Zahedan",
  "Bilaspur",
  "Louisville",
  "San Jose Del Monte",
  "Hillah",
  "Kryvyi Rih",
  "Yaroslavl",
  "Brighton",
  "Feira De Santana",
  "Vladivostok",
  "Comilla",
  "Tlaxcala",
  "Siping",
  "Sanhe",
  "Calabar",
  "Mathura",
  "Abakaliki",
  "Xinmi",
  "Skopje",
  "Makhachkala",
  "Tomsk",
  "Jingjiang",
  "Shishi",
  "Fuqing",
  "Sanliurfa",
  "Leipzig",
  "Agartala",
  "Xiantao",
  "Yichun Heilongjiang",
  "Imphal",
  "Daye",
  "Mbeya",
  "Cenxi",
  "Kingston",
  "Sangli",
  "Cuiaba",
  "Samarkand",
  "Malaga",
  "Ibague",
  "Dortmund",
  "Kagoshima",
  "Cabimas",
  "Qitaihe",
  "Milwaukee",
  "Catania",
  "Samut Sakhon",
  "Likasi",
  "Beira",
  "Hamadan",
  "Shuozhou",
  "Tonghua",
  "Djibouti",
  "Essen",
  "Toulon",
  "Dresden",
  "Juiz De Fora",
  "Bouake",
  "Pereira",
  "Udaipur",
  "Sanmenxia",
  "Vellore",
  "Dongyang",
  "Ardabil",
  "Thoothukkudi",
  "Bloemfontein",
  "Xinyi",
  "Udon Thani",
  "Ogbomosho",
  "Jalgaon",
  "Hebi",
  "Zaoyang",
  "Yiyang Hunan",
  "Gaya",
  "Baltimore",
  "Yazd",
  "Tirunelveli",
  "Zhaodong",
  "Dengfeng",
  "Matamoros",
  "Kitchener",
  "Poza Rica De Hidalgo",
  "Oujda",
  "Santa Fe",
  "Cuito",
  "Orenburg",
  "Cangzhou",
  "Jiaozhou",
  "Kemerovo",
  "Bremen",
  "Karbala",
  "Al Mansurah",
  "Weinan",
  "Anyang",
  "Mazar E Sharif",
  "Kota Kinabalu",
  "Basel",
  "Gomel",
  "Albuquerque",
  "Gaozhou",
  "Feicheng",
  "Meknes",
  "Panipat",
  "Kahramanmaras",
  "Irbid",
  "Arak",
  "Tepic",
  "Chiang Rai",
  "Guangyuan",
  "Leicester",
  "Tongchuan",
  "Khamis Mushayt",
  "Ndola",
  "Tucson",
  "Imus",
  "Villavicencio",
  "Sakarya",
  "Bamenda",
  "Shouguang",
  "Utrecht",
  "Rajahmundry",
  "Novokuznetsk",
  "Larkana",
  "Basilan City",
  "Valledupar",
  "Chaoyang",
  "Uige",
  "Hamhung",
  "Sukkur",
  "Rayong",
  "Port Of Spain",
  "Kerman",
  "Abeokuta",
  "Mekele",
  "Yongkang",
  "Edinburgh",
  "Haining",
  "San Juan",
  "Ryazan",
  "Vilnius",
  "Taishan",
  "Calamba",
  "Mesa",
  "Hannover",
  "Fresno",
  "Chuzhou",
  "Namangan",
  "Pingdu",
  "Al Mukalla",
  "Qingzhou",
  "Longkou",
  "Naberezhnye Tchelny",
  "Astrakhan",
  "Santa Marta",
  "Ambon",
  "Bellary",
  "Diwaniyah",
  "Pietermaritzburg",
  "Rustenburg",
  "Heyuan",
  "Yanshi",
  "Al Raqqa",
  "Surakarta",
  "Dali",
  "Sheikhupura",
  "Changning",
  "Grenoble",
  "Puerto Vallarta",
  "Balashikha",
  "Angeles City",
  "Gombe",
  "Hosur",
  "Poznan",
  "Gongyi",
  "Van",
  "Gaoyou",
  "Shizuishan",
  "El Djelfa",
  "Kikwit",
  "Ar Rusayfah",
  "Vale Do Aco",
  "Cuautla Morelos",
  "Sacramento",
  "Kalasin",
  "Shangyu",
  "Atlanta",
  "Al Mahallah Al Kubra",
  "Loum",
  "Laixi",
  "Kakinada",
  "Rupganj",
  "Penza",
  "Berbera",
  "Utsunomiya",
  "Porto Velho",
  "Davanagere",
  "Qianjiang",
  "Chuxiong",
  "Songyuan",
  "Duisburg",
  "Nakhon Pathom",
  "Muzaffarpur",
  "Mataram",
  "Mbouda",
  "Zinder",
  "Changge",
  "Kirov",
  "Kuantan",
  "Ziyang",
  "Xingning",
  "Kandahar",
  "Nurenberg",
  "London Ca",
  "Eslamshahr",
  "Bournemouth",
  "Jinjiang",
  "Khon Kaen",
  "Cheboksary",
  "Matsuyama",
  "Tanta",
  "Shuangyashan",
  "Lipetsk",
  "Karaganda",
  "Changyi",
  "Arusha",
  "Murcia",
  "Malatya",
  "Guang An",
  "Tirana",
  "Surat Thani",
  "Kansas City",
  "Ubon Ratchathani",
  "Kolwezi",
  "Kabinda",
  "Jianyang",
  "Douai Lens",
  "Nanping",
]

table = {}

def addWord(w):
    letters = [c for c in w if c in string.ascii_letters]
    w = ''.join(letters)
    
    for i in range(0, len(w) - 1):
        j = i + 1
        ci = w[i]
        cj = w[j]
        #print ("pair", ci, cj)

        oldTab = table.get(ci, {})
        oldVal = oldTab.get(cj, 0)
        oldTab[cj] = oldVal + 1
        table[ci] = oldTab
    c_last = w[-1]
    oldTab = table.get(c_last, {})
    oldVal = oldTab.get('$', 0)
    oldTab['$'] = oldVal + 1
    table[c_last] = oldTab

for name in city_names:
    for w in name.split():
        w = w.strip()
        if len(w) < 4:
            continue
        w = w.lower()
        print(w)
        addWord(w)
        
tableKeys = list(table.keys())
tableKeys.sort()

for tk in tableKeys:
    print("=== {0} ===".format(tk))

    freqList = []
    
    for key, val in table[tk].items():
        freqList.append((val, key))
    freqList.sort()
    freqList.reverse()
    for kv in freqList:
        print(kv)
    print()


print()
print()

for tk in tableKeys:
    freqList = []
    
    for key, val in table[tk].items():
        freqList.append((val, key))
    freqList.sort()
    freqList.reverse()

    s = ""
    for key, value in freqList[:5]:
        s = s + value
    while len(s) < 5:
        s = s + "$"
    print ('({0}, "{1}"),'.format(tk, s))
    
