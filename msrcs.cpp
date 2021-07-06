/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msrcs.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 20:00:32 by vvaucoul          #+#    #+#             */
/*   Updated: 2021/07/06 20:30:04 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <vector>

#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <dirent.h>

class Msrcs {
private:
	std::string		_folder;

	std::vector<std::string> _files_path;

public:
	Msrcs (std::string const &folder);
	~Msrcs();

	int process();
	int rec(std::string const &dir_name);

	void	get_result() {
		for (std::vector<std::string>::iterator it = _files_path.begin(); it != _files_path.end(); it++) {
			std::cout << *it << '\n';
		}
	}
};

Msrcs::Msrcs(std::string const &folder) : _folder(folder) {
	DIR		*dir;

	if (!(dir = opendir(_folder.c_str())))
		throw std::string("Error, invalid folder");
}
Msrcs::~Msrcs() {

}

int	Msrcs::rec(std::string const &dir_name) {
	DIR			*dir;

	struct dirent *sdir = NULL;

	//std::cout << "Try to open : " << dir_name << '\n';

	if (!(dir = opendir(dir_name.c_str())))
		throw std::string("Error, invalid folder");

	while ((sdir = readdir(dir)) != NULL) {
		if (!(std::string(sdir->d_name)).compare(".") || !(std::string(sdir->d_name)).compare(".."))
			continue;
		//std::cout << "DIr : " << sdir->d_name << '\n';
		if (sdir->d_type == DT_DIR)
			rec(dir_name + "/" + sdir->d_name);
		else if (sdir->d_type == DT_REG)
			_files_path.push_back(dir_name + "/" + sdir->d_name);
	}
	closedir(dir);
	return (0);
}

int Msrcs::process(void) {

	rec(_folder);

	return (0);
}

/*
**	MAIN
*/

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Error, usage : msrcs folder" << '\n';
		return (-1);
	}
	else
	{
		std::string folder = std::string(argv[1]);
		try
		{
			Msrcs m(folder);

			m.process();
			m.get_result();
		}
		catch (std::string &e)
		{
			std::cerr << e << '\n';
			return (-1);
		}
	}
	return (0);
}
