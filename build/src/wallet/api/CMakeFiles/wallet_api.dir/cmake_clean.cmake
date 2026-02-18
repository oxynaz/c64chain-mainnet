file(REMOVE_RECURSE
  "../../../lib/libwallet_api.a"
  "../../../lib/libwallet_api.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang CXX)
  include(CMakeFiles/wallet_api.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
