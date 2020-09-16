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
sys_install unzip
sys_install curl
sys_install cmake

case "$os" in
		opensuse)
			sys_install libirrlicht-dev
			;;
		archlinux)
			sys_install libirrlicht-dev
			;;
		fedora)
			sys_install irrlicht-devel
			;;
		debian)
			sys_install libirrlicht-dev
			;;
		gentoo)
			sys_install libirrlicht-dev
			;;
	esac

cd /tmp
curl -O http://www.ambiera.at/downloads/irrKlang-64bit-1.6.0.zip
unzip -o irrKlang-64bit-1.6.0.zip
cd irrKlang-64bit-1.6.0/
sudo mkdir -p /usr/include/irrklang
sudo mkdir -p /usr/lib64
sudo cp -f ./include/* /usr/include/irrklang/
sudo cp -f ./bin/linux-gcc-64/libIrrKlang.so /usr/lib64
sudo cp -f ./bin/linux-gcc-64/libIrrKlang.so /usr/lib