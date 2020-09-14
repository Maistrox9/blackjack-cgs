#include "headers/card.h"

Card::Card(char rank, char suit) {
	this->rank = rank;
	this->suit = suit;
	std::string rank_str = "";
	rank_str.push_back(rank);
	switch(suit) {
		case 'D':
			this->ui_cardv = {".------.", 
							"|" + rank_str + ".--. |", 
							R"(| :/\: |)", 
							R"(| :\/: |)", 
							"| '--'" + rank_str + "|",
							"`------'"};
			break;
		case 'S':
			this->ui_cardv = {".------.", 
							"|" + rank_str + ".--. |", 
							R"(| :/\: |)", 
							R"(| (__) |)", 
							"| '--'" + rank_str + "|",
							"`------'"};
			break;
		case 'H':
			this->ui_cardv = {".------.", 
							"|" + rank_str + ".--. |", 
							R"(| (\/) |)", 
							R"(| :\/: |)", 
							"| '--'" + rank_str + "|",
							"`------'"};
			break;
		case 'C':
			this->ui_cardv = {".------.", 
							"|" + rank_str + ".--. |", 
							R"(| :(): |)", 
							R"(| ()() |)", 
							"| '--'" + rank_str + "|",
							"`------'"};
			break;
	}
}

char Card::get_rank() {
	return this->rank;
}

char Card::get_suit() {
	return this->suit;
}

std::string Card::get_card() {
	return this->rank + "-" + this->suit;
}

std::vector<std::string> Card::get_ui_cardv() {
	return this->ui_cardv;
}
