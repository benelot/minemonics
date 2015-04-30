/*
 * NameGenerator.cpp
 *
 *  Created on: Mar 13, 2015
 *      Author: leviathan
 */

//# corresponding header
#include <utils/NameGenerator.hpp>
#include <string>

//## controller headers

//## model headers

//## view headers

//# custom headers
//## base headers

//## configuration headers

//## controller headers

//## model headers

//## view headers

//## utils headers

NameGenerator::NameGenerator() {
	initialize();

}

NameGenerator::~NameGenerator() {
	// TODO Auto-generated destructor stub
}

void NameGenerator::initialize() {
	//Here I will create an array of prefixes to help generate names.
	// I am banking on multiplication to ensure a large number of names
	// by using 7 prefixes and 20 stems, and 16 suffixes I should be able to
	// create about 7 * 20 * 16 = 2240 names out of 312 bytes of data (In my earlier
	// example from the forum I used this code to generate male and female names,
	// but here I combined them).
	std::string namePrefix[] = {
			"", //who said we need to add a prefix?
			"bel", //lets say that means "the good"
			"nar", //"The not so good as Bel"
			"xan", //"The evil"
			"bell", //"the good"
			"natr", //"the neutral/natral"
			"ev", //Man am I original
			//dwarfish
			"B", "Gil", "Bal", "Gim", "Bel", "Kil", "Bof", "Mor", "Bol", "Nal",
			"D", "Nor", "Dal", "Ov", "Dor", "Th", "Dw", "Thor", "Far", "Thr",
			//elvish
			"Aer", "Af", "Ah", "Al", "Am", "Ama", "An", "Ang", "Ansr", "Ar",
			"Arì", "Arn", "Aza", "Bael", "Bes", "Cael", "Cal", "Cas", "Cla",
			"Cor", "Cy", "Dae", "Dho", "Dre", "Du", "Eil", "Eir", "El", "Er",
			"Ev", "Fera", "Fi", "Fir", "Fis", "Gael", "Gar", "Gil", "Ha", "Hu",
			"Ia", "Il", "Ja", "Jar", "Ka", "Kan", "Ker", "Keth", "Koeh", "Kor",
			"La", "Laf", "Lam", "Lue", "Ly", "Mai", "Mal", "Mara", "My", "Na",
			"Nai", "Nim", "Nu", "Ny", "Py", "Raer", "Re", "Ren", "Ru", "Rua",
			"Rum", "Rid", "Sae", "Seh", "Sel", "Sha", "She", "Si", "Sim", "Sol",
			"Sum", "Syl", "Ta", "Tahl", "Tha", "Tho", "Ther", "Thro", "Tia",
			"Tra", "Uth", "Ver", "Vil", "Von", "Ya", "Za", "Zy",
			//men
			"Adan", "Beo", "Grim", "Ceol", "Esc", "Theod", "Elf", "Esc",
			"Beord", "Cwen", "Leof", "Here", "Wulf", "Beleg", "Fela", "Gil",
			"Curu", "Ul", "Breg", "Hir", "Ir", "Rod", "Sael", "Bel", "Galadh",
			"Nim", "Tinu", "Edhel",
			//hobbits
			"Ever", "Ferd", "Isen", "Dino" };

	mNamePrefix.assign(namePrefix,
			namePrefix + sizeof(namePrefix) / sizeof(namePrefix[0]));

	std::string nameSuffix[] = { "", "us", "ix", "ox", "ith", "ath", "um",
			"ator", "or", "axia", "imus", "ais", "itur", "orex", "o", "y",
			//dwarfish
			"aim", "a", "ain", "ala", "ak", "ana", "ar", "ip", "i", "ia", "ur",
			"ona", "im", "ila", "in", "ina", "or", "ola", "o", "on",
			//elvish
			"ael", "aer", "aera", "aias", "aia", "ah", "aha", "aith", "aira",
			"al", "ala", "la", "lae", "llae", "ali", "am", "ama", "an", "ana",
			"a", "ani", "uanna", "ar", "ara", "ra", "ari", "ri", "aro", "ro",
			"as", "ash", "sah", "ath", "avel", "brar", "abrar", "ibrar", "dar",
			"adar", "odar", "deth", "eath", "eth", "dre", "drim", "drimme",
			"udrim", "dul", "ean", "el", "ele", "ela", "emar", "en", "er",
			"erl", "ern", "ess", "esti", "evar", "fel", "afel", "efel", "hal",
			"ahal", "ihal", "har", "ihar", "uhar", "hel", "ahel", "ihel", "ian",
			"ianna", "ia", "ii", "ion", "iat", "ik", "il", "iel", "ila", "lie",
			"im", "in", "inar", "ine", "ir", "ira", "ire", "is", "iss", "ist",
			"ith", "lath", "lith", "lyth", "kash", "ashk", "okash", "ki", "lan",
			"lanna", "lean", "olan", "ola", "lam", "ilam", "ulam", "lar",
			"lirr", "las", "lian", "lia", "lis", "elis", "lys", "ellon", "lyn",
			"llinn", "lihn", "mah", "ma", "mahs", "mil", "imil", "umil", "mus",
			"nal", "inal", "onal", "nes", "nin", "nine", "nyn", "nis", "anis",
			"oth", "othi", "que", "quis", "rah", "rae", "raee", "rad", "rahd",
			"rail", "ria", "aral", "ral", "ryl", "ran", "re", "reen", "reth",
			"rath", "ro", "ri", "ron", "ruil", "aruil", "eruil", "sal", "isal",
			"sali", "san", "sar", "asar", "isar", "sel", "asel", "isel", "sha",
			"she", "shor", "spar", "tae", "itae", "tas", "itas", "ten", "iten",
			"thal", "tha", "ethal", "etha", "thar", "ethar", "ithar", "ther",
			"ather", "thir", "thi", "ethil", "thil", "thus", "thas", "aethus",
			"aethas", "ti", "eti", "til", "tril", "tria", "atri", "atril",
			"atria", "ual", "lua", "uath", "luth", "uth", "us", "ua", "van",
			"vanna", "var", "vara", "avar", "avara", "vain", "avain", "via",
			"avia", "vin", "avin", "wyn", "ya", "yr", "yn", "yth", "zair",
			"zara", "azair", "ezara",
			//men
			"ferth", "helm", "laf", "wald", "wine", "wulf", "flaed", "leofu",
			"bur", "wen", "gifu", "waru", "swith", "randir", "thelion", "dor",
			"born ", "uil", "dal", "ieth", "iel", "rian", "wing", "uial", "los",
			"uilos",
			//hobbits
			"acar", "gard", "fast", "wise", "mond" };

	mNameSuffix.assign(nameSuffix,
			nameSuffix + sizeof(nameSuffix) / sizeof(nameSuffix[0]));

	std::string nameStems[] = { "", "adur", "aes", "anim", "apoll", "imac",
			"educ", "equis", "extr", "guius", "hann", "equi", "amora", "hum",
			"iace", "ille", "inept", "iuv", "obe", "ocul", "orbis" };

	mNameStems.assign(nameStems,
			nameStems + sizeof(nameStems) / sizeof(nameStems[0]));
}

std::string NameGenerator::generateName() {
	std::string newName;
	newName.append(
			mNamePrefix.at(mRandomness.nextPosInt(0, mNamePrefix.size() - 1)));
	if (mRandomness.nextPosInt(0, 1)) {
		newName.append(
				mNameStems.at(
						mRandomness.nextPosInt(0, mNameStems.size() - 1)));
	}
	newName.append(
			mNameSuffix.at(mRandomness.nextPosInt(0, mNameSuffix.size() - 1)));

	//Make the first letter capital...
	newName[0] = toupper(newName.at(0));
	return newName;
}
