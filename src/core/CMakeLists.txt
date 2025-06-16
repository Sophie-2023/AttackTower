add_library(lib_core
  
  
  
  
  
  
  
  
  
  
  
  

 "Game.cpp" "Game.h"  "Troupe.h" "Chasseur.h" "Chasseur.cpp" "Troupe.cpp" "TroupeFactory.cpp"  "TroupeManager.h" "TroupeManager.cpp" "TroupeFactory.h" "Loup.h" "Loup.cpp" "State.h" "EtatEnRoute.h" "EtatEnRoute.cpp" "Champ.h" "Champ.cpp" "Carte.h" "Carte.cpp" "Defense.h" "Defense.cpp" "TourDeGuet.h" "TourDeGuet.cpp" "EtatCombat.cpp" "EtatCombat.h" "EtatExploitation.h" "EtatExploitation.cpp" "EtatRetour.h" "EtatRetour.cpp" "Lieu.h" "Lieu.cpp" "CanonABle.h" "CanonABle.cpp" "Base.h" "Base.cpp" "Foret.h" "Foret.cpp" "Soldat.h" "Soldat.cpp" "End.h" "End.cpp")



target_include_directories(lib_core PUBLIC ./)
target_link_libraries(lib_core PUBLIC pugixml sfml-graphics)
