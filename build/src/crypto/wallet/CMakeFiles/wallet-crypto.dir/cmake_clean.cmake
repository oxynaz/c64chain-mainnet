file(REMOVE_RECURSE
  "libwallet-crypto.a"
  "libwallet-crypto.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang ASM C)
  include(CMakeFiles/wallet-crypto.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
