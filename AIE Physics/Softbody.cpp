#include "Softbody.h"
#include "Circle.h"
#include "Spring.h"

void Softbody::Build(PhysicsScene* a_scene, glm::vec2 a_position, float a_spacing, float a_springForce, float a_damping, std::vector<std::string>& a_strings)
{
    int numColumns = a_strings.size();
    int numRows = a_strings[0].length();

    // traverse across the array and add balls where the ascii art says they should be
    Circle** circle = new Circle* [numRows * numColumns];
    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numColumns; j++)
        {
            if (a_strings[j][i] == '0')
            {
                circle[i * numColumns + j] = new Circle(a_position + glm::vec2(i,
                    j) * a_spacing, glm::vec2(0, 0), 1.0f, 2.0f, glm::vec4(1, 0, 0, 1));
                a_scene->AddActor(circle[i * numColumns + j]);
            }
            else
            {
                circle[i * numColumns + j] = nullptr;
            }
        }
    }

    for (int i = 1; i < numRows; i++)
    {
        for (int j = 1; j < numColumns; j++)
        {
            Circle* s11 = circle[i * numColumns + j];
            Circle* s01 = circle[(i - 1) * numColumns + j];
            Circle* s10 = circle[i * numColumns + j - 1];
            Circle* s00 = circle[(i - 1) * numColumns + j - 1];

            // make springs to cardinal neighbours 
            if (s11 && s01) a_scene->AddActor(new Spring(s11, s01, a_damping, a_springForce));
            if (s11 && s10) a_scene->AddActor(new Spring(s11, s10, a_damping, a_springForce));
            if (s10 && s00) a_scene->AddActor(new Spring(s10, s00, a_damping, a_springForce));
            if (s01 && s00) a_scene->AddActor(new Spring(s01, s00, a_damping, a_springForce));

            //create diagonal springs
            if (s11 && s00) a_scene->AddActor(new Spring(s11, s00, a_damping, a_springForce));
            if (s01 && s10) a_scene->AddActor(new Spring(s01, s10, a_damping, a_springForce));

            bool endOfJ = j == numColumns - 1;
            bool endOfI = i == numRows - 1;

            Circle* s22 = (!endOfI && !endOfJ) ? circle[(i + 1) * numColumns + (j + 1)] : nullptr;
            Circle* s02 = !endOfJ ? circle[(i - 1) * numColumns + (j + 1)] : nullptr;
            Circle* s20 = !endOfI ? circle[(i + 1) * numColumns + j - 1] : nullptr;

            if (s22 && s02) a_scene->AddActor(new Spring(s22, s02, a_damping, a_springForce));
            if (s22 && s20) a_scene->AddActor(new Spring(s22, s20, a_damping, a_springForce));
            if (s20 && s00) a_scene->AddActor(new Spring(s20, s00, a_damping, a_springForce));
            if (s02 && s00) a_scene->AddActor(new Spring(s02, s00, a_damping, a_springForce));
        }
    }
}