# test 1
ADD_EXECUTABLE( testTools testTools.cxx ../displayTools.cxx )
TARGET_LINK_LIBRARIES( testTools ${VTK_LIBRARIES} )
ADD_TEST(NAME testTools COMMAND $<TARGET_FILE:testTools> )

# test 2
ADD_EXECUTABLE( testQtDisplay testQtDisplay.cxx ../meshQtDisplay.cxx ../displayTools.cxx )
TARGET_LINK_LIBRARIES( testQtDisplay ${VTK_LIBRARIES} ${QT_LIBRARIES} )
ADD_TEST(NAME testQtDisplay COMMAND $<TARGET_FILE:testQtDisplay> )
