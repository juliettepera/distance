# test 1
ADD_EXECUTABLE( testData testTools.cxx ../data.cxx )
TARGET_LINK_LIBRARIES( testData ${VTK_LIBRARIES} )
ADD_TEST(NAME testData COMMAND $<TARGET_FILE:testData> )

# test 2
ADD_EXECUTABLE( testDisplay testQtDisplay.cxx ../display.cxx ../data.cxx )
TARGET_LINK_LIBRARIES( testDisplay ${VTK_LIBRARIES} ${QT_LIBRARIES} )
ADD_TEST(NAME testDisplay COMMAND $<TARGET_FILE:testDisplay> )
