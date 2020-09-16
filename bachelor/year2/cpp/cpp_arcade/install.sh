#!/usr/bin/env bash

function get_os_type
{
	which zypper &> /dev/null && os="opensuse"
	which pacman &> /dev/null && os="archlinux"
	which dnf &> /dev/null && os="fedora"
	which apt-get &> /dev/null && os="debian"
	which emerge &> /dev/null && os="gentoo"
}


function handle_error
{
	result=$1
	if test $result -eq 0; then
		return
	else
		line "#" $C_RED
		line "#" $C_YELLOW
		echo -en $C_RED"[Erreur]"$C_RST" lors de l'installation, voulez-vous arreter le script ? [O/n]  "
		read stop_script
		case $stop_script in
			n|N)	return;;
			*)		exit 1;;
		esac
	fi
}

function sys_install
{
	package_name=$1

	function get_cmd_install
	{
		case "$os" in
			opensuse)
				echo "zypper -y install"
				;;
			archlinux)
				echo "pacman --noconfirm -S"
				;;
			fedora)
				echo "dnf -y install"
				;;
			debian)
				echo "apt-get -y install"
				;;
			gentoo)
				echo "emerge"
				;;
		esac
	}

	if test -z "$cmd_install"; then
		cmd_install=$(get_cmd_install)
	fi

	sudo $cmd_install $package_name
	handle_error $?
}

function update
{
case "$os" in
		opensuse)
			sudo zypper -y update
			;;
		archlinux)
			sudo pacman --noconfirm -Syu
			;;
		fedora)
			sudo dnf -y update
			;;
		debian)
			sudo apt-get -y update; sudo apt-get -y upgrade
			;;
		gentoo)
			sudo emerge -u world
			;;
	esac
}

get_os_type
update
#INSTALL CLANG
sys_install clang

#INSTALL LIBNCURSES5
sys_install libncurses5

#INSTALL LIBSMFL2.4
sys_install libsfml-audio2.4
sys_install libsfml-graphics2.4
sys_install libsfml-network2.4
sys_install libsfml-system2.4
sys_install libsfml-window2.4

#INSTALL LIBCACA
sys_install libcaca0