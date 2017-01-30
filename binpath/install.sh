#!/bin/bash

echo "BinPath 0.1 Installer"
echo "Install BinPath to your home directory."
echo

echo -n "Press \"Y\" to continue... "

read -s -n 1 REPLY

if [ "$REPLY" != "y" -a "$REPLY" != "Y" ]; then
	
	echo "user canceled."
	exit 1
	
fi

echo "continuing."
echo

i_assert ()
{
	if ! "$@"; then
		
		echo
		echo "Sorry... Installation is failed :("
		
		exit 1
		
	fi
}

echo -n "Make directories... "

i_assert mkdir -p "${HOME}/.binpath"
i_assert mkdir -p "${HOME}/.binpath/sto"
i_assert mkdir -p "${HOME}/.binpath/sto/bindir"
i_assert mkdir -p "${HOME}/.binpath/sto/mounts"

echo "done"

echo -n "Copying files... "

i_assert cp -R bin "${HOME}/.binpath"
i_assert cp -R lib "${HOME}/.binpath"

echo "done"

echo -n "Writing configurations... "

n_temp="$(mktemp)"
i_assert test $? -eq 0

cat << _EOF > "$n_temp"
# BinPath 0.1 Install Configuration
# Written on $(date)

export BINPAT_BIN="${HOME}/.binpath/bin"
export BINPAT_LIB="${HOME}/.binpath/lib"
export BINPAT_STO="${HOME}/.binpath/sto"

_EOF

n_c1="${HOME}/.binpath/lib/bashrc.sh.head"
n_c2="${HOME}/.binpath/lib/bashrc.sh.tail"

cat "$n_c1" "$n_temp" "$n_c2" > "${HOME}/.binpath/lib/bashrc.sh"
i_assert test $? -eq 0

i_assert rm "$n_c1" "$n_temp" "$n_c2"

echo "done"

echo -n "Fixing permissions... "

i_assert find "${HOME}/.binpath/bin" -type f -exec chmod 500 {} ";"
i_assert find "${HOME}/.binpath/lib" -type f -exec chmod 400 {} ";"

echo "done"

echo -n "Hooking .bashrc... "

i_assert cp "${HOME}/.bashrc" "${HOME}/.bashrc~"

echo ". ${HOME}/.binpath/lib/bashrc.sh" >> "${HOME}/.bashrc"
i_assert test $? -eq 0

echo "done"

echo
echo "Installation is finished! Have a nice day :)"

