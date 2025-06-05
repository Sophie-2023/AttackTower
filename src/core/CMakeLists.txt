add_library(lib_core
  
  
  
  
  
  
  
  
  
  
  
  
 "Game.cpp" "Game.h"  "Troupe.h" "Chasseur.h" "Chasseur.cpp" "Troupe.cpp" "TroupeFactory.cpp"  "TroupeManager.h" "TroupeManager.cpp" "TroupeFactory.h" "Loup.h" "Loup.cpp" "State.h" "EtatEnRoute.h" "EtatEnRoute.cpp" "Champ.h" "Champ.cpp" "Carte.h" "Carte.cpp"  )
target_include_directories(lib_core PUBLIC ./)
target_link_libraries(lib_core PUBLIC pugixml sfml-graphics)
