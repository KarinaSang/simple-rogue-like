#include "merchant.h"

Merchant::Merchant (shared_ptr <Cell> t) : treasure{t} {
	//adjust base ratio of merchant
	// ...
	hostile = false;
}

//
