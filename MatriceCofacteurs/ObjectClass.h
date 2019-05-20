#pragma once

class ObjectClass {
public:
	ObjectClass(int value) {
		this->value = value;
	}
	ObjectClass() {
		this->value = 2;
	}

	int getValue() { return value; }

private:
	int value;
};

std::ostream &operator<<(std::ostream &out, ObjectClass &objectClass) {
	out << objectClass.getValue();
	return out;
}