#include <iostream>
#include <iomanip>
#include <ostream>
#include <functional>
#include <string>

constexpr float HamwiMultiplierMale = 2.7f;
constexpr float HamwiWeightFactorMale = 48.0f;
constexpr float HamwiMultiplierFemale = 2.2f;
constexpr float HamwiWeightFactorFemale = 45.5f;
constexpr float MetersToInches = 39.37008f;
constexpr float FiveFeetInInches = 60.0f;

enum class Gender {
	Male, Female
};

class Weight {
private:
	long double Kilograms;
public:
	Weight(long double&& kilos) noexcept : Kilograms(kilos) {}
	Weight(long double& kilos) noexcept : Kilograms(kilos) {}

	long double getKilograms() const { return Kilograms; }
};

class Height {
private:
	long double Meters;
public:
	Height(long double&& meters) noexcept : Meters(meters) {}
	Height(long double& meters) noexcept : Meters(meters) {}

	long double getMeters() const { return Meters; }
};

std::ostream& operator << (std::ostream& outstream, Weight& weight) { outstream << weight.getKilograms(); return outstream; }
std::ostream& operator << (std::ostream& outstream, Height& height) { outstream << height.getMeters(); return outstream; }

Weight&& operator"" _kgs(long double kgs) { return std::move(Weight(kgs)); }
Height&& operator"" _mts(long double mts) { return std::move(Height(mts)); }

Weight HamwiIdealWeight(const Height height_in_meters, const Gender& gender)
{
	Weight result_weight(0.0_kgs);
	long double ideal_weight = (height_in_meters.getMeters() * MetersToInches) - FiveFeetInInches;
	
	switch (gender)
	{
		case Gender::Male:
			ideal_weight *= HamwiMultiplierMale;
			ideal_weight += HamwiWeightFactorMale;
			result_weight = ideal_weight;
			return result_weight;

		case Gender::Female:
			ideal_weight *= HamwiMultiplierFemale;
			ideal_weight += HamwiWeightFactorFemale;
			result_weight = ideal_weight;
			return result_weight;
	}
}

int main()
{
	long double height_input;
	char gender_input;
	std::cout << "Enter you height in meters (eg: 1.45) and gender to receive your ideal weight.\n";
	std::cout << "Enter your height:\n";
	std::cin >> height_input;
	std::cout << "Enter you gender (f for female and m for male):\n";
	std::cin >> gender_input;

	Height myHeight(height_input);
	Gender myGender;
	
	switch (gender_input)
	{
	case 'f':
		myGender = Gender::Female;
		break;
	case 'm':
		myGender = Gender::Male;
		break;
	default:
		std::cout << "That's not a valid option.\n";
		break;
	}

	Weight myIdealWeight = HamwiIdealWeight(myHeight, myGender);

	std::cout << std::setprecision(4) << myIdealWeight << "\n";

	return 0;
}