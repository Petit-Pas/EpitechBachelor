/*l
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Internal functions
*/

#ifndef CPP_PLAZZA_PLAZZA_HPP
# define CPP_PLAZZA_PLAZZA_HPP

#define SHIFT_IN_OUT_MQ 8000
#define ID_DONE_FILE_MQ 3

namespace plz {
	extern bool endG;

	enum Information {
		PHONE_NUMBER,
		EMAIL_ADDRESS,
		IP_ADDRESS
	};

	typedef struct Task {
		char outFileName[512];
		char filename[256];
		Information information;
	} Task;

	typedef struct MainData {
		Task asked;
		int usePercentage;
		int waitingListState;
		bool timeout;
	} MainData;
}

#endif //CPP_PLAZZA_PLAZZA_HPP
