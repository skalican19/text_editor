
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ios>
#include <regex>

bool is_number(std::string s) {
	return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
}

std::ostringstream init_working_file(std::string file_path) {
	std::ifstream file(file_path);
	std::ostringstream working_file;

	std::string temp;
	while (std::getline(file, temp)) {
		working_file << temp << std::endl;
	}

	return working_file;
}

std::vector<std::string> read_cin() {
	std::vector<std::string> input;
	std::string temp;
	while (1) {
		std::getline(std::cin, temp);
		if (temp == ".") { break; }
		input.push_back(temp);
	}
	return input;
}

void save_file(std::ostringstream& file, std::string file_path) {
	std::ofstream output(file_path);
	output << file.str();
	output.close();
}

std::pair<int, int> parse_range(std::string range) {
	std::regex reg("^([0-9]*,?[0-9]*)$");
	int from = 1; //od zaciatku
	int to = INT_MAX; //po koniec

	if (range == "") {
		return { 1, INT_MAX };
	}

	//pokial je range v spravnom tvare
	if (std::regex_match(range, reg)) {

		size_t comm_pos = range.find(",");

		//ak je ciarka na zaciatku
		if (comm_pos == 0) {
			//pokial je za ciarkou cislo
			if (range.size() > 1) {
				to = std::stoi(range.substr(1));
			}
		}

		//ak je ciarka na hocijakej pozicii
		else if (comm_pos != std::string::npos) {
			from = std::stoi(range.substr(0, comm_pos));
			//pokial nieje ciarka na konci
			if (!(comm_pos == range.size() - 1)) {
				to = std::stoi(range.substr(comm_pos + 1));
			}
		}
		//pokial sa ciarka nenachadza
		else if (comm_pos == std::string::npos) {
			from = std::stoi(range);
			to = std::stoi(range);
		}
	}
	else {
		return { 0, 0 };
	}
	if (to < from) {
		return { -1, 0 };
	}
	return { from, to };
}

void change_in_file(std::ostringstream& working_file, std::pair<int, int> range, std::vector<std::string> to_change) {
	std::stringstream file;
	file << working_file.str();

	working_file.str("");

	int i = 1;
	std::string temp;
	while (std::getline(file, temp)) {
		if (i < range.first || i > range.second) {
			working_file << temp << std::endl;
		}
		if (i == range.first) {
			for (std::string line : to_change) {
				working_file << line << std::endl;
			}
		}
		i++;
	}
}

void change(std::ostringstream& working_file, std::string input) {
	std::vector<std::string> to_change;
	std::pair<int, int> range = { 1, INT_MAX };
	std::string temp;

	if (input == "") {
		to_change = read_cin();
	}
	else {
		size_t wl_pos = input.find(" ");
		std::string range_str = input.substr(0, wl_pos);

		range = parse_range(range_str);

		if (range.first == 0) {
			range = { 1, INT_MAX };
			to_change.push_back(input);
		}
		else if (range.first == -1) {
			std::cout << "Invalid range" << std::endl;
		}
		else {
			if (wl_pos != std::string::npos) {
				temp = input.substr(wl_pos);
				wl_pos = temp.find_first_not_of(" ");
				if (wl_pos != std::string::npos) {
					to_change.push_back(temp.substr(wl_pos));
				}
			}
			else {
				to_change = read_cin();
			}
		}
	}
	change_in_file(working_file, range, to_change);
}

void print_from_file(std::ostringstream& working_file, std::string input) {
	std::pair<int, int> range = parse_range(input);

	if (range.first == 0 || range.first == -1) {
		size_t wl_pos = input.find(" ");
		if (wl_pos != std::string::npos) std::cout << "Unsupported command" << std::endl;
		else std::cout << "Invalid range" << std::endl;
		return;
	}

	std::stringstream file;
	file << working_file.str();


	int i = 1;
	std::string temp;

	while (std::getline(file, temp)) {
		if (range.first <= i && i <= range.second) {
			std::cout << temp << std::endl;
		}
		i++;
	}
}

void delete_from_file(std::ostringstream& working_file, std::string input) {
	std::pair<int, int> range = parse_range(input);

	if (range.first == 0 || range.first == -1) {
		size_t wl_pos = input.find(" ");
		if (wl_pos != std::string::npos) std::cout << "Unsupported command" << std::endl;
		else std::cout << "Invalid range" << std::endl;
		return;
	}

	std::stringstream file;
	file << working_file.str();

	working_file.str("");

	int i = 1;
	std::string temp;
	while (std::getline(file, temp)) {
		if (i < range.first || i > range.second) {
			working_file << temp << std::endl;
		}
		i++;
	}
}

void append_to_file(std::ostringstream& working_file, int64_t line_num, std::vector<std::string> to_append) {
	std::stringstream file;
	file << working_file.str();

	working_file.str("");
	working_file.clear();

	int i = 1;
	std::string temp;
	while (std::getline(file, temp) || i <= line_num) {
		working_file << temp << std::endl;
		temp = "";
		if (i == line_num) {
			for (std::string line : to_append) {
				working_file << line << std::endl;
			}
		}
		i++;
	}
	if (line_num == -1) {
		for (std::string line : to_append) {
			working_file << line << std::endl;
		}
	}
}

void append(std::ostringstream& working_file, std::string input) {
	std::vector<std::string> to_append;
	std::string temp;
	int line = -1;
	if (input == "") {
		to_append = read_cin();
	}
	else {
		//najdi prvu medzeru
		size_t wl_pos = input.find(" ");
		std::string line_str = input.substr(0, wl_pos);

		if (wl_pos != std::string::npos) {
			temp = input.substr(wl_pos);
		}

		//pokial line nie je cislo, je to onliner a appendi string	
		if (!is_number(line_str)) {
			to_append.push_back(input);
		}

		else {
			//ak zaèína string sledom medzier, orez a appendni
			wl_pos = temp.find_first_not_of(" ");
			line = std::stoi(line_str);

			if (wl_pos != std::string::npos) {
				to_append.push_back(temp.substr(wl_pos));
			}
			//inak nacitaj zo vstupu
			else {
				to_append = read_cin();
			}
		}
	}

	append_to_file(working_file, line, to_append);
}

void quit(std::ostringstream& working_file, std::string file_path) {
	std::ostringstream file = init_working_file(file_path);

	if (file.str() == working_file.str()) {
		exit(0);
	}

	std::cout << "You have unsaved changes" << std::endl;
	return;
}

void parse_command(std::ostringstream& working_file, std::string input, std::string file_path) {
	size_t wl_pos = input.find(" ");
	std::string cmd = input.substr(0, wl_pos);
	std::string argument = "";

	if (wl_pos != std::string::npos) {
		input = input.substr(wl_pos);
		wl_pos = input.find_first_not_of(" ");
		if (wl_pos != std::string::npos) {
			argument = input.substr(wl_pos);
		}
	}

	if (cmd == "a") {
		append(working_file, argument);
	}
	else if (cmd == "w" && wl_pos == std::string::npos) {
		save_file(working_file, file_path);
	}
	else if (cmd == "q" && wl_pos == std::string::npos) {
		quit(working_file, file_path);
	}
	else if (cmd == "p") {
		print_from_file(working_file, argument);
	}
	else if (cmd == "d") {
		delete_from_file(working_file, argument);
	}
	else if (cmd == "c") {
		change(working_file, argument);
	}
	else if (cmd == "q!" && wl_pos == std::string::npos) {
		exit(0);
	}
	else {
		std::cout << "Unsupported command" << std::endl;
	}

}

int main(int argc, char* argv[])
{
	if (argc == 2) {
		std::string input;
		std::ostringstream working_file = init_working_file(argv[1]);
		std::cout << "* ";

		while (std::getline(std::cin, input)) {
			if (input != "") parse_command(working_file, input, argv[1]);
			else std::cout << "Unsupported command" << std::endl;
			std::cout << "* ";
		}
	}
	return 0;
}