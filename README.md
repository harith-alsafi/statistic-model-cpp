# Table of content 
- [Features](#features)
- [Code and screenshots](#code-and-screenshots)
- [Project overview](#project-overview)
- [Detailed design](#detailed-design)
  * [misc.hpp](#mischpp)
  * [regr.hpp](#regrhpp)
  * [intp.hpp](#intphpp)
  * [menu.hpp](#menuhpp)
- [Mathematical design](#mathematical-design)
- [Reference](#reference)

# Features 

* The program is divided into three parts 

  * Statistical analysis 
    * Users can load CSV files as they are prompted  
    * Users can save CSV files 
    * The CSV file is encapsulated file into a ``misc::Table`` class 
    * Viewing content of CSV files 
      * Showing all rows 
      * Showing certain number of rows 
      * Showing certain column 
      * Showing certain row 
    * Statistical analysis of all columns in the table 
      * Standard deviation and variance 
      * Mean and Summation 
      * Maximum value and minimum value 
      * 25th percentile, median and 75th percentile 
      * Interquartile range (IQR)

  * Regression 
    * Correlation coefficient 
    * Plots original data, and predicted data 
    * Plots the equation with 500 points with the minimum and maximum of the loaded x-data  
    * Shows a table containing  x-values, y-values and the predicted data 
    * Linear regression shows slope and y-intersect in equation form
    * Polynomial regression shows coefficients of polynomials within the equation which is printed as a latex view 
  * Interpolation 
    * Plots original data
    * Plots all possible interpolations for 500 points with the minimum and maximum of the loaded x-data  
    * Gets the user's x-input and returns the interpolated output , in the same time this output gets stored in the vector and can be viewed as a table at any time 
    * Shows a table x-values, y-values and the interpolated data 
    * Applies either linear interpolation or polynomial interpolation 
  * Error warning and crash prevention against:
    * miss-loaded data 
    * No read CSV files 
    * Out of bounds input 
    * Wrong data type input 

# Code and screenshots 

* Screenshots 

  * Main menu 

  ![image-20211210114443425](https://i.imgur.com/NuMBPv3.png)

  * Option-1

  ![image-20211210114512952](https://i.imgur.com/Tv3gUcV.png)

  * Option-2

    ![image-20211210114543717](https://i.imgur.com/sn3qW6D.png)

     * Sub-option-1 (it keeps going)

    ![image-20211210114718904](https://i.imgur.com/u4Vfobz.png)

     * Sub-option-2

    ![image-20211210114747902](https://i.imgur.com/iULetFk.png)

     * Sub-option-3

    ![image-20211210114806074](https://i.imgur.com/G7SY4GA.png)

     * Sub-option-4	

    ![image-20211210114837387](https://i.imgur.com/KUqAPIv.png)

  * Option-3 (``statistics.csv`` is loaded)

  ![image-20211210114915002](https://i.imgur.com/z1Smk7j.png)

  * Option-4

    ![image-20211210114956569](https://i.imgur.com/2TqHNiA.png)

    * Sub-option-1

      * Linear 

      ![image-20211210115131461](https://i.imgur.com/E5oXciN.png)

      * Polynomial 

      ![image-20211210115459232](https://i.imgur.com/l5UK7YX.png)

    * Sub-option-2

      * Linear 

      ![image-20211210115200240](https://i.imgur.com/33F2a9l.png)

      ![image-20211210115221062](https://i.imgur.com/IjQd1om.png)

      ![image-20211210115240990](https://i.imgur.com/TLaISOL.png)

      * Polynomial 

      ![image-20211210115537511](https://i.imgur.com/kfheYsZ.png)

      ![image-20211210115555109](https://i.imgur.com/Wvsm1wY.png)

      ![image-20211210115638213](https://i.imgur.com/JQ0KeuZ.png)

    * Sub-option-3

    ![image-20211210115327360](https://i.imgur.com/Qcr7p49.png)

  * Option-5

    ![image-20211210115921631](https://i.imgur.com/fIdwNp1.png)

    * Sub-option-1

    ![image-20211210115849857](https://i.imgur.com/RwG1chn.png)

    * Sub-option-2

    ![image-20211210115958484](https://i.imgur.com/0FHns1I.png)

    * Sub-option-3

      * Linear 

      ![image-20211210120039712](https://i.imgur.com/jmeXE48.png)

      ![image-20211210120056815](https://i.imgur.com/0fodBQS.png)

      * Polynomial 

      ![image-20211210120755319](https://i.imgur.com/6i5WBQl.png)

      ![image-20211210120807800](https://i.imgur.com/cBSlqJU.png)

    * Sub-option-4

    ![image-20211210120709181](https://i.imgur.com/hXjvrPI.png)

  * Option-6

    ![image-20211210123043442](https://i.imgur.com/kILHLMy.png)

* This is the code as a ``.zip`` file:



# Project overview 

* The software design of this project will be similar to a library design approach as it will have the following features such as:
  * It will be header based, as all files will be in ``.hpp`` 
  * The use of a build system such as **Cmake** 
  * The use of a testing framework such as **Google Test** (GTest)
  * Complex directory system 
  * Full and detailed code documentation 
  * Use of namespace and classes 
  * Use of object oriented programming such as inheritance and collaboration 
  * Use of version control such as **git** 

* Directory structure 

  * What is each directory 
    * ``doc/`` documentation directory for any documentation material 
    * ``out/`` output directory to store compiled outputs  
    * ``include/`` include directory for all of the source code 
    * ``lib/`` library directory to store any external libraries 
    * ``test/`` testing directory to store any test scripts 
  * The current structure 

  ```
  include
  ├── graphs.hpp
  ├── intp.hpp
  ├── menu.hpp
  ├── misc.hpp
  └── regr.hpp
  test
  ├── int_test.cpp
  ├── menu_test.cpp
  ├── misc_test.cpp
  └── reg_test.cpp
  out
  ├── interpolation.csv
  ├── regression.csv
  ├── statistics.csv
  ├── test_int
  ├── test_menu
  └── test_reg
  build
  └──...
  lib
  └── googletest
  doc
  └──... 
  
  CMakeLists.txt
  ```

* Libraries and dependencies used 

  * Libraries 
    * Google test for testing (https://github.com/google/googletest)
    * Tables and Graphs for the terminal graphing (https://github.com/tdulcet/Tables-and-Graphs )
    * Standard library 
      * ``iterator``
      * ``utility`` 
      * ``fstream`` 
      * ``string`` 
      * ``vector`` 
      * ``algorithm`` 
      * ``numeric`` 
      * ``iostream``  
  * Test script dependency flow chart 

  <img src="https://i.imgur.com/a54lQop.png" alt="test_menu" style="zoom:200%;" />

  * Main program (``menu.hpp``) dependency flow chart 

  <img src="https://i.imgur.com/kApZFmT.png" alt="menu-file-dependency" style="zoom: 200%;" />

  * Both figures show how the dependencies are used such ``graph.hpp`` and ``gtest.h`` are the external libraries 
  * The Cmake build script 

```cmake
######################## project details ##########################
cmake_minimum_required(VERSION 3.13)

# Enable debug symbols by default
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()

# project detail
project(mcpp VERSION 1.0 DESCRIPTION "Statistical model")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../out)

# cpp standard (c++14)
set(CMAKE_CXX_STANDARD 14)

include_directories(includes)
include_directories(test/)

add_subdirectory(lib/googletest EXCLUDE_FROM_ALL)

# reg
add_executable(test_reg test/reg_test.cpp)

# misc
add_executable(test_misc test/misc_test.cpp)

# int 
add_executable(test_int test/int_test.cpp)

# menu 
add_executable(test_menu test/menu_test.cpp)

target_link_libraries(test_reg gtest pthread) 
target_link_libraries(test_misc gtest pthread) 
target_link_libraries(test_int gtest pthread) 
```

* Git log  (https://github.com/harith-alsafi/statistic-model-cpp) 

```
24377de6de2ff6535fe0331048c3e2a44be12497 changed documentation
97e947ebb93475b9911620b25386f6b2aefdede8 fixed documentation
2102f546e5618bb7d12afa2a3aca7f1f662cf350 added files
d8e4267113b8564147917e188d65b233dbad4de6 fixed csv
894dbd2c04d21ef5c0ff833c8cd67316ce10ad7a finished everything
b1b2b3d3cc40686fbf29664e20f354c6992fef26 finalized documentation
9189429c6c3ec6a8e6aa0a4061bad4650ab9e2cd finishde intp.hpp
7aa0493f0d984c3813ad9df98d6726bfb5756075 finished documenting misc.hpp
5e1332c1a10f44cc0fc26127f16d02b4dfcdbef4 finalized everything
fba32bf5ea45edd10d2ce9f0d75d18a06a86a9b4 finished polynomial
cdd7008e3e8d408ec72baf549d28d5f9790cff81 finished poly (almost)
87aa4050372b44b8de3a9502c8d5c5293ea9fa8e polynomial isnt working for real life data
3f618b0cba6d9f9cd34b9480b092f24e2093cb42 finished up the menu [almost]
fcd0e588c52bed6efa3485e33d4a4fcc6bc9b52d finishing up regression
f0ce1ee27deba868628dc62eec2ffb11954af76e almost finished option for show data
a803eda7b8e6fa0cfb092c5de6567a80e878c19a finishing up the menu
d6c26c236c12c9a5d265af2f3ea6e6b0de470edd started with menu options
80dbf36da54d500560f2f4b1492b82cecb7a8279 finished polyinterp
2dfd42dfc03d2d2dcd709ecc180c73894330eda5 finished testing linerinterp
b3314b4eaebacaefaab56b3abb97a14f683b758b cleaning up a bit of the code
e960e121c87c22ff5bbd99a2104d852d9c9e68cc started testing intp
477724c717b7dee948440978bf46980b38316eae almost finishing up linearinterpolation
5949f356d03305b0e93b80fc5802363935d06abb finishing up LinearRegression
6c546ce0997cf6932022c547d324afd9eff81966 fixed naming scheme
86aab0d1a023a7f10bfa6546b0ed69a17bf3c059 adding more features
308bea5874622c6cb103dbe3aafed3eb92cadb51 cleaning up the enviroment
8f81d1924d29eb0fa8eb0c24f049bd55e3ed92a2 finished table
bee2a6b73fe160d4e2498fb3e331bdc8fa23274c did changes to plot and added to table
01508cdae75b4463239d7b975086f111f60ca834 directory structure and code
17a548d5ef8e836059f2244d431d049daa45c018 directory structure
c0ac4a63a52e070a85824966f170432f58349423 Initial commit
```

# Detailed design 

* Namespaces and classes 
  * We have multiple namespaces (N) and multiple classes (C)
  * The figure below summarises the existing namespaces with their corresponding classes
  * The main class that is used to run the menu is ``Menu`` 
  * It encapsulates all methods and classes into a CLI interface

![namespaces-and-classes](https://i.imgur.com/jNLyjNX.png)

## misc.hpp

* Holds ``misc`` namespace which stands for miscellaneous
* Dependencies 

![misc-hpp-dependency](https://i.imgur.com/tYgsCQl.png)

* Global functions 

  * ``misc.hpp`` has only two global functions outside the namespace as shown below:

    ![global-functions](https://i.imgur.com/bJQr2uE.png)

  * The reason that they are global is that one of them overload an existing function which is ``round`` such that it gives the ability to specify the number of decimal places 

  * The other function implements a multiplication operator for ``std::vector`` 

  * Both of those functions are templated meaning they can take any data type 

  * I wanted to implement this method in other classes however ``graph.hpp`` uses long double, thus I was forced to use long double

  * Another way could have been to convert any data type into long double before using ``graph.hpp`` however this is not practical as I will be repeating many lines of code which is inefficient.  

* Functions inside the namespace 

  ![misc-functions](https://i.imgur.com/3ocudSx.png)

  * This the only function that doesnt belong to any class but is within the namepsace 
  * It is used to generate an ``std::vector`` of any type given the minimum and maximum values with the number of points of that ``std::vector`` 

* ``Plot`` class 

  * Collaboration diagram 

    ![collaboration-Plot](https://i.imgur.com/Mb6lfJ4.png)

  * The collaboration diagram will show any class that ``Plot`` has used within its attributes such as:

    * ``graphoptions`` which is part of ``graph.hpp`` , the variable is ``aoptions`` 
    * ``std::string`` which is part of ``<string>`` , the variable is ``title`` 

  * The collaborative variables are shown as pointing towards the class

  * The diagram shows all methods and attributes of the class such that 

    * Private methods and attributes are denoted by ``-`` (ex: ``height``)
    * Public methods and attributes are denoted by ``+`` (ex: ``Plot()``)

  * It also contains an enum variable which holds the colours to use in ``graph.hpp``  

  ![enum-Plot-Color](https://i.imgur.com/kOKj1aZ.png)

  * This is a description of the attributes 

  ![image-20211210054612697](https://i.imgur.com/rJ7rffm.png)

* ``Table `` class 

  * Collaboration diagram 

    ![collaboration-Table](https://i.imgur.com/AXE1U43.png)

  * We can see that this diagram is a bit different that the previous one such that we have an arrow going from the class itself 

  * This is because this class uses inheritance as it inherits from a standard library which is ``std::vector<std::vector<long double>>`` 

  * There is a ``QR`` struct within this class which is as follows:

  ![Collaboration graph](https://i.imgur.com/RjiYzvZ.png)

  ![image-20211210054830062](https://i.imgur.com/Kc6ekXS.png)

  * This struct will be used to store the Quartiles range for a given vector 

* What files uses ``misc.hpp`` 

![misc-usage](https://i.imgur.com/i42TcuA.png)

## regr.hpp

* Holds ``regr`` namespace which stands for regression

* Dependencies 

![regr-file-dependency](https://i.imgur.com/fsNmZIQ.png)

* This file doesn't contain any global functions inside or outside the namespace 

* ``LinearRegression`` class

  * Collaboration diagram 

    ![collaboration-LinearRegression](https://i.imgur.com/iMHhMck.png)

  * We can see that this class also uses a ``misc::Plot`` variable, which the reason its shown in the diagram 

  * ``misc::Table`` was also used but mainly as a return type as shown below:

  ![regr-misc-table-usage](https://i.imgur.com/OykSER9.png)

  * All of the heavy mathematical algorithms are done in ``fit_data()`` 

  * We also have ``virtual`` functions such that they will be overloaded by the following class which is ``PolyRegression``  

    ![image-20211210051347851](https://i.imgur.com/U1HXB14.png)

    ![image-20211210051406129](https://i.imgur.com/NtDjK7V.png)

  * This class has the following ``friend`` class as it will ease up integrating both classes 

  ![image-20211210052749858](https://i.imgur.com/LvsktFe.png)

  * The attributes of the class will store the main variables that will be used with regression 

  ![image-20211210053938056](https://i.imgur.com/2kmy4Ji.png)

* ``PolyRegression`` class 

  * Collaboration diagram

  ![collaboration-PolyRegression](https://i.imgur.com/hihVahP.png)

  * This class inherits from ``LinearRegression`` and overloads the ``virtual`` methods 
  * And as the same concept most of the mathematical algorithms were implemented in ``fit_data()`` 
  * This class also declares a few methods of ``LinearRegression`` as private since they are not suited for a polynomial regression such as:

  ![image-20211210052839198](https://i.imgur.com/W3y6hDE.png)

  * The new attributes added are as follows:

    ![image-20211210055131953](https://i.imgur.com/ZuGUwwR.png)

  * Where as the new added function are specifically used for this class:

    * ``set_degree()`` sets the degree 
    * ``get_power()`` returns a ``std::string`` of the x superscript based on given power 

* What files use ``regr.hpp`` 

![regre-file-usage](https://i.imgur.com/7waMudh.png)

## intp.hpp

* Holds ``intp`` namespace which stands for interpolation 

* Dependencies 

![intp-file-dependency](https://i.imgur.com/lpXiaA2.png)

* This file doesn't contain any global functions inside or outside the namespace 

* ``LinearInterp`` class

  * Collaboration diagram 

    ![collaboration-LinearInterp](https://i.imgur.com/Z4jvGt9.png)

  * This one uses the same concept as ``LinearRegression`` when it comes to the design 

  * Most of the numerical algorithms occur in ``find_value()`` 

  * ``plot_all_interpolation()`` will be used to showcase the true intent of this program 

  * This class also has virtual methods which are:

  ![image-20211210060230343](https://i.imgur.com/RWX8qBr.png)

  ![image-20211210060301656](https://i.imgur.com/muJSUDe.png)

  * This class also has a ``friend`` class which is as follows:

  ![image-20211210060342826](https://i.imgur.com/jQiNPHV.png)

  * The following is the description of the attributes 

  ![image-20211210060629926](https://i.imgur.com/5oSMaiH.png)

* ``PolyInterp`` class 

  * Collaboration diagram 

    ![collaboration-PolyInterp](https://i.imgur.com/TXAFD2D.png)

  * This class inherits from ``LinearInterp`` 

  * It only overrides the ``virtual` functions without adding any new methods or attributes 

* What files use ``intp.hpp ``

![intp-file-usage](https://i.imgur.com/jdEFOHU.png)

## menu.hpp

* Holds the CLI implementation of the program within the ``Menu`` class 

* The dependency diagram is the same for the one used for the whole diagram 

* ``Menu`` class 

  * Collaboration diagram 

  ![collaboration-menu](https://i.imgur.com/qrqX8Ry.png)

  * Since this class uses all the previous classes, this is the reason that the diagram looks complex 
  * The class also has an ``enum`` as follows :

  ![enum-Menu](https://i.imgur.com/U91ZDJB.png)

  * This variable will control the flow of the program such as the program will have sub menus, meaning that I need to keep the program in the sub menus until prompted to go back

  * The following is a description of the attributes 

  ![image-20211210062233778](https://i.imgur.com/vlgXbh4.png)

  * The only function that will be used is ``run()`` which will start the menu
  * This is implemented in this way such that its easier to use implement in other files 

#  Mathematical design 

* Representation of the arrays

![image-20211210064413236](https://i.imgur.com/3dFBXG7.png)

* Statistical analysis 

  * Mean

    ![image-20211210064350747](https://i.imgur.com/UCcy9vK.png)

    * Assuming we have an array of n-values, we loop through the array and sum up all of the values
    * Then we divide by the number of this array 

  * Standard deviation and variance

    ![image-20211210082940329](https://i.imgur.com/b61DQQI.png)

    *  We loop through the elements 
    * Subtract each element from the mean and square the result 
    * Add up all the elements and then divide by the total number of elements of the array 

  * Interquartile range

    ![image-20211210082923599](https://i.imgur.com/zqYprJz.png)

    * You need to sort the area before implementing the equation 
    * The output of the Quartiles would be the index of the array 

  * Co-relation coefficient 

    ![image-20211210082912739](https://i.imgur.com/YqqsQxg.png)

    * This will implement the sum function that I made
    * It will also use the multiplication operator for the vectors
    * Having those two methods made implementing this equation much simpler 

* Linear regression 

  ![image-20211210082856590](https://i.imgur.com/N3lwRt4.png)

  * This uses the same concept as the correlation coefficient 
  * So I calculate the numerator and denominator through the previous functions 
  * Then calculate the corresponding slope (m) and y-intercept (c) 

* Polynomial regression (m is the degree)

  ![image-20211210082833367](https://i.imgur.com/5LyWoAA.png)

  * We can see that the polynomial regression is more complex compared to the linear one
  * Through code it can be simplified such as in order to get the matrix **X** we need a few loops that calculates the power or each x-value and assign it into the correct place of the matrix 
  * The first equation shows the representation of each row
  * This means that we will have a system of linear equations 
  * Using the concept of linear algebra specifically  Gaussian elimination we are able to solve for a
  * Since one of my team-mates was implementing such algorithms I borrowed some of his code to solve the linear system 

* Linear interpolation 

  ![image-20211210082955581](https://i.imgur.com/UGyFtVA.png)

  * First we need to sort the array in ascending order
  * Then we extract the upper and lower bound that x-input lies in between
  * We extract the corresponding y-value of the upper and lower bounds 
  * Then we calculate the interpolated y-value 

* Polynomial interpolation (Lagrange interpolation)

  ![image-20211210083755384](https://i.imgur.com/HKairP4.png)

  * So we declare a nested for loop such that we calculate the difference and then multiply it with the previous difference unit we get the value 
  * Then we calculate the interpolated-y through the summation of the product of each y-value with what we got from the previous equation 

# Reference 

* https://www.calculatorsoup.com/calculators/statistics/average.php
* http://strata.uga.edu/8370/lecturenotes/variance.html
* https://laptrinhx.com/quartile-formula-3982131609/
* https://www.statisticshowto.com/probability-and-statistics/correlation-coefficient-formula/
* https://www.statisticshowto.com/probability-and-statistics/regression-analysis/find-a-linear-regression-equation/
* https://en.wikipedia.org/wiki/Polynomial_regression
* https://theeducationlife.com/interpolation-formula/
* https://www.math.usm.edu/lambers/mat772/fall10/lecture5.pdf