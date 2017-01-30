# BinPath Routine: Bindir Management
# Manage bindirs by registering, unregistering & listing.

declare -a BINPAT_R_LIST=("register" "unregister" "list")

# Routine 1: Register

BINPAT_R_register_USAGE="NAME [PATH]"
BINPAT_R_register_DESCR="Register bindir to PATH"

binpat_r_register_parse ()
{
	BINPAT_R_register_A_NAME="$1"
	BINPAT_R_register_A_PATH="$2"
}

binpat_r_register_exec()
{
	local n_file="${BINPAT_STO}/bindir/${BINPAT_R_register_A_NAME}"
	local n_path="$(realpath "${BINPAT_R_register_A_PATH}")"
	
cat << _EOF > "${n_file}"
#!/bin/bash

# BinPath 0.1 Bindir Wrapper
# Written on $(date)

BINPAT_B_PATH="${n_path}"
source ${BINPAT_LIB}/bindir.sh

_EOF
	
	chmod 755 "${n_file}"
	
}

# Routine 2: Unregister

BINPAT_R_unregister_USAGE="NAME"
BINPAT_R_unregister_DESCR="Unregister bindirs from PATH"

binpat_r_unregister_parse ()
{
	BINPAT_R_unregister_A_NAME="$1"
}

binpat_r_unregister_exec()
{
	local n_file="${BINPAT_STO}/bindir/${BINPAT_R_unregister_A_NAME}"
	rm "${n_file}"
}

# Routine 3: List

BINPAT_R_list_USAGE=""
BINPAT_R_list_DESCR="List registered name"

binpat_r_list_parse ()
{
	return
}
binpat_r_list_exec()
{
	ls "${BINPAT_STO}/bindir"
}

