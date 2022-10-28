#include "nata.h"

namespace Nata
{
	namespace Exercises
	{
        int HelloTriangle_0()
        {
            Window* win = new Window("Nata Engine", 960, 540);
            Input* input = win->GetInput();

            //
            // Initializing Shader Program object
            // 
            // Reading vertex shader file from path
            std::string tempVertPath = FileUtils::ReadFile("src\\shaders\\basic.vert");
            const char* vertPath = tempVertPath.c_str();

            // Creating vertex shader object
            unsigned int vertShader;
            vertShader = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vertShader, 1, &vertPath, NULL);
            glCompileShader(vertShader);

            int success;
            char infoLog[512];
            glGetShaderiv(vertShader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(vertShader, 512, NULL, infoLog);
                std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
            }

            // Reading fragment shader file from path
            std::string tempFragPath = FileUtils::ReadFile("src\\shaders\\basic.frag");
            const char* fragPath = tempFragPath.c_str();

            // Creating fragment shader object
            unsigned int fragShader;
            fragShader = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragShader, 1, &fragPath, NULL);
            glCompileShader(fragShader);

            glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(vertShader, 512, NULL, infoLog);
                std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
            }

            // PROGRAM
            // Shader program object is final linked version of multiple shaders combined
            unsigned int shaderProgram;
            shaderProgram = glCreateProgram();
            glAttachShader(shaderProgram, vertShader);
            glAttachShader(shaderProgram, fragShader);
            glLinkProgram(shaderProgram);

            glGetShaderiv(shaderProgram, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
                std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
            }

            // Delete shaders once they've been linked to program
            glDeleteShader(vertShader);
            glDeleteShader(fragShader);

            // Data to render
            float vertices[] =
            {
                // positions         // colors
                 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
                -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
                 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
            };

            //
            // 1. Initializing objects
            // 
            unsigned int VAO;
            glGenVertexArrays(1, &VAO);
            glBindVertexArray(VAO);

            unsigned int VBO;
            glGenBuffers(1, &VBO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);

            // 
            // 2. Sending data to objects
            //
            // Data to render (vertices and indices)
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

            // Set how to interpret data
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(0));
            glEnableVertexAttribArray(0);

            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
            glEnableVertexAttribArray(1);

            //

            int vertexColorLocation = glGetUniformLocation(shaderProgram, "Color");

            while (!win->Closed())
            {
                win->Clear();
                
                glUseProgram(shaderProgram);

                float time = glfwGetTime();
                float greenValue = (sin(time) / 2.0f) + 0.5f;
                glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

                glBindVertexArray(VAO);
                glDrawArrays(GL_TRIANGLES, 0, 3);
                glBindVertexArray(NULL);

                win->Update();
            }
            // Clean/deleted all allocated resources
            glfwTerminate();
            return 0;
        }

		int HelloTriangle_1()
		{
            Window* win = new Window("Nata Engine", 960, 540);
            Input* input = win->GetInput();

            float vertices[] =
            {
                -1.f, -0.5f, 0.f,
                -0.5f, 0.5f, 0.f,
                 0.f, -0.5f, 0.f,

                 0.f, -0.5f, 0.f,
                 0.5f, 0.5f, 0.f,
                 1.f, -0.5f, 0.f,
            };

            unsigned int indices[] =
            {  // note that we start from 0!
                0, 1, 3,   // first triangle
                1, 2, 3    // second triangle
            };

            //
            // 1. Initializing objects
            // 
            // Creating and binding Vertex Array Object
            unsigned int VAO;
            glGenVertexArrays(1, &VAO);
            glBindVertexArray(VAO);

            // Creating and binding Vertex Buffer Object
            unsigned int VBO;
            glGenBuffers(1, &VBO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);

            // Creating and binding Element Buffer Object
            unsigned int EBO;
            glGenBuffers(1, &EBO);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

            // 
            // 2. Sending data to objects
            //
            // Data to render (vertices and indices)
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

            // Set how to interpret data
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);
            glEnableVertexAttribArray(0);

            //
            // 3. Initializing Shader Program object
            // 
            // Create shaders and program object

            // Reading vertex shader file from path
            std::string tempVertPath = FileUtils::ReadFile("src\\shaders\\basic.vert");
            const char* vertPath = tempVertPath.c_str();

            // Creating vertex shader object
            unsigned int vertShader;
            vertShader = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vertShader, 1, &vertPath, NULL);
            glCompileShader(vertShader);

            int success;
            char infoLog[512];
            glGetShaderiv(vertShader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(vertShader, 512, NULL, infoLog);
                std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
            }

            // Reading fragment shader file from path
            std::string tempFragPath = FileUtils::ReadFile("src\\shaders\\basic.frag");
            const char* fragPath = tempFragPath.c_str();

            // Creating fragment shader object
            unsigned int fragShader;
            fragShader = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragShader, 1, &fragPath, NULL);
            glCompileShader(fragShader);

            glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(vertShader, 512, NULL, infoLog);
                std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
            }

            // PROGRAM
            // Shader program object is final linked version of multiple shaders combined
            unsigned int shaderProgram;
            shaderProgram = glCreateProgram();
            glAttachShader(shaderProgram, vertShader);
            glAttachShader(shaderProgram, fragShader);
            glLinkProgram(shaderProgram);

            glGetShaderiv(shaderProgram, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
                std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
            }

            // Delete shaders once they've been linked to program
            glDeleteShader(vertShader);
            glDeleteShader(fragShader);

            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

            while (!win->Closed())
            {
                win->Clear();
                //
                // 4. Rendering
                // 
                // Every shader and rendering call after this willl use this program object
                glUseProgram(shaderProgram);
                glBindVertexArray(VAO);

                glDrawArrays(GL_TRIANGLES, 0, 6);

                glBindVertexArray(NULL);
                win->Update();
            }
            // Clean/deleted all allocated resources
            glfwTerminate();
            return 0;
		}

        int HelloTriangle_2_3()
        {
            Window* win = new Window("Nata Engine", 960, 540);
            Input* input = win->GetInput();

            std::string tempVertPath = FileUtils::ReadFile("src\\shaders\\basic.vert");
            const char* vertPath = tempVertPath.c_str();

            unsigned int vertShader;
            vertShader = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vertShader, 1, &vertPath, NULL);
            glCompileShader(vertShader);

            int success;
            char infoLog[512];
            glGetShaderiv(vertShader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(vertShader, 512, NULL, infoLog);
                std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
            }

            // Reading fragment shader file from path
            std::string tempFragPath = FileUtils::ReadFile("src\\shaders\\basic.frag");
            const char* fragPath = tempFragPath.c_str();

            // Creating fragment shader object
            unsigned int fragShader;
            fragShader = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragShader, 1, &fragPath, NULL);
            glCompileShader(fragShader);

            glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(vertShader, 512, NULL, infoLog);
                std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
            }

            // PROGRAM
            // Shader program object is final linked version of multiple shaders combined
            unsigned int shaderProgram;
            shaderProgram = glCreateProgram();
            glAttachShader(shaderProgram, vertShader);
            glAttachShader(shaderProgram, fragShader);
            glLinkProgram(shaderProgram);

            glGetShaderiv(shaderProgram, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
                std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
            }

            unsigned int shaderProgram2;
            shaderProgram2 = glCreateProgram();
            glAttachShader(shaderProgram2, vertShader);

            tempFragPath = FileUtils::ReadFile("src\\shaders\\test2.frag");
            fragPath = tempFragPath.c_str();
            fragShader = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragShader, 1, &fragPath, NULL);
            glCompileShader(fragShader);

            glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(vertShader, 512, NULL, infoLog);
                std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
            }
            
            glAttachShader(shaderProgram2, fragShader);
            glLinkProgram(shaderProgram2);

            // Delete shaders once they've been linked to program
            glDeleteShader(vertShader);
            glDeleteShader(fragShader);

            //
            // VERTEX DATA
            //
            float vertices1[] =
            {
                -1.f, -0.5f, 0.f,
                -0.5f, 0.5f, 0.f,
                 0.f, -0.5f, 0.f,
            };

            float vertices2[] =
            {
                0.f, -0.5f, 0.f,
                0.5f, 0.5f, 0.f,
                1.f, -0.5f, 0.f,
            };

            //
            // 1. Initializing objects
            // 
            unsigned int VAOs[2];
            glGenVertexArrays(2, VAOs);
            unsigned int VBOs[2];
            glGenBuffers(2, VBOs);

            // 
            // 2. Sending data to objects
            //
            glBindVertexArray(VAOs[0]);
            glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);
            glEnableVertexAttribArray(0);

            
            glBindVertexArray(VAOs[0]);
            glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);
            glEnableVertexAttribArray(0);

            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

            while (!win->Closed())
            {
                win->Clear();
                glUseProgram(shaderProgram);
                glBindVertexArray(VAOs[0]);
                glDrawArrays(GL_TRIANGLES, 0, 3);

                glUseProgram(shaderProgram2);
                glBindVertexArray(VAOs[1]);
                glDrawArrays(GL_TRIANGLES, 0, 3);

                glBindVertexArray(NULL);
                win->Update();
            }

            glfwTerminate();
            return 0;
        }

        int Shaders_0()
        {
            Window* win = new Window("Nata Engine", 960, 540);
            Input* input = win->GetInput();
            
            float vertices[] =
            {
                -1.f, -0.5f, 0.f,
                -0.5f, 0.5f, 0.f,
                 0.f, -0.5f, 0.f,
            
                 0.f, -0.5f, 0.f,
                 0.5f, 0.5f, 0.f,
                 1.f, -0.5f, 0.f,
            };
            
            unsigned int indices[] =
            {  // note that we start from 0!
                0, 1, 3,   // first triangle
                1, 2, 3    // second triangle
            };
            
            //
            // 1. Initializing objects
            // 
            // Creating and binding Vertex Array Object
            unsigned int VAO;
            glGenVertexArrays(1, &VAO);
            glBindVertexArray(VAO);
            
            // Creating and binding Vertex Buffer Object
            unsigned int VBO;
            glGenBuffers(1, &VBO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            
            // Creating and binding Element Buffer Object
            unsigned int EBO;
            glGenBuffers(1, &EBO);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            
            // 
            // 2. Sending data to objects
            //
            // Data to render (vertices and indices)
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
            
            // Set how to interpret data
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);
            glEnableVertexAttribArray(0);
            
            //
            // 3. Initializing Shader Program object
            // 
            // Create shaders and program object
            
            // Reading vertex shader file from path
            std::string tempVertPath = FileUtils::ReadFile("src\\shaders\\basic.vert");
            const char* vertPath = tempVertPath.c_str();
            
            // Creating vertex shader object
            unsigned int vertShader;
            vertShader = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vertShader, 1, &vertPath, NULL);
            glCompileShader(vertShader);
            
            int success;
            char infoLog[512];
            glGetShaderiv(vertShader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(vertShader, 512, NULL, infoLog);
                std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
            }
            
            // Reading fragment shader file from path
            std::string tempFragPath = FileUtils::ReadFile("src\\shaders\\basic.frag");
            const char* fragPath = tempFragPath.c_str();
            
            // Creating fragment shader object
            unsigned int fragShader;
            fragShader = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragShader, 1, &fragPath, NULL);
            glCompileShader(fragShader);
            
            glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(vertShader, 512, NULL, infoLog);
                std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
            }
            
            // PROGRAM
            // Shader program object is final linked version of multiple shaders combined
            unsigned int shaderProgram;
            shaderProgram = glCreateProgram();
            glAttachShader(shaderProgram, vertShader);
            glAttachShader(shaderProgram, fragShader);
            glLinkProgram(shaderProgram);
            
            glGetShaderiv(shaderProgram, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
                std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
            }
            
            // Delete shaders once they've been linked to program
            glDeleteShader(vertShader);
            glDeleteShader(fragShader);
            
            while (!win->Closed())
            {
                win->Clear();
                //
                // 4. Rendering
                // 
                // Every shader and rendering call after this willl use this program object
                glUseProgram(shaderProgram);
                glBindVertexArray(VAO);
            
                glDrawArrays(GL_TRIANGLES, 0, 6);
            
                glBindVertexArray(NULL);
                win->Update();
            }
            // Clean/deleted all allocated resources
            glfwTerminate();
            return 0;
        }

        int Shaders_1()
        {
            Window* win = new Window("Nata Engine", 960, 540);
            Input* input = win->GetInput();

            Shader* shader = new Shader("src\\shaders\\test.vert", "src\\shaders\\test.frag");

            // Data to render
            float vertices[] =
            {
                // positions         // colors
                 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
                -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
                 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
            };

            //
            // 1. Initializing objects
            // 
            unsigned int VAO;
            glGenVertexArrays(1, &VAO);
            glBindVertexArray(VAO);

            unsigned int VBO;
            glGenBuffers(1, &VBO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);

            // 
            // 2. Sending data to objects
            //
            // Data to render (vertices and indices)
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

            // Set how to interpret data
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(0));
            glEnableVertexAttribArray(0);

            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
            glEnableVertexAttribArray(1);

            //


            while (!win->Closed())
            {
                win->Clear();

                shader->Enable();

                float time = glfwGetTime();
                float greenValue = (sin(time) / 2.0f) + 0.5f;
                shader->SetUniform4f("Color", 0.0f, greenValue, 0.0f, 1.0f);
                shader->SetUniform2f("Offset", vec2(1.f, 1.f));

                glBindVertexArray(VAO);
                glDrawArrays(GL_TRIANGLES, 0, 3);
                glBindVertexArray(NULL);

                shader->Disable();

                win->Update();
            }
            // Clean/deleted all allocated resources
            glfwTerminate();
            return 0;
        }

        int Textures_1()
        {
            Window* win = new Window("Nata Engine", 960, 540);
            Input* input = win->GetInput();

            // build and compile our shader zprogram
            // ------------------------------------
            Shader ourShader("src\\shaders\\test.vert", "src\\shaders\\test.frag");

            // set up vertex data (and buffer(s)) and configure vertex attributes
            // ------------------------------------------------------------------
            float vertices[] = 
            {
                // positions          // colors           // texture coords
                 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
                 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
                -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
                -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
            };

            unsigned int indices[] = 
            {
                0, 1, 3, // first triangle
                1, 2, 3  // second triangle
            };

            unsigned int VBO, VAO, EBO;
            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBO);
            glGenBuffers(1, &EBO);

            glBindVertexArray(VAO);

            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

            // position attribute
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            // color attribute
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
            glEnableVertexAttribArray(1);
            // texture coord attribute
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
            glEnableVertexAttribArray(2);


            // Initializing Texture 1
            unsigned int texture1;

            glGenTextures(1, &texture1);
            glBindTexture(GL_TEXTURE_2D, texture1);
            // set the texture wrapping parameters
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            // set texture filtering parameters
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            // load image, create texture and generate mipmaps
            int width, height, nrChannels;
            stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
            unsigned char* data = stbi_load("res\\container.jpg", &width, &height, &nrChannels, 0);
            if (data)
            {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(GL_TEXTURE_2D);
            }
            else
            {
                std::cout << "Failed to load texture" << std::endl;
            }
            stbi_image_free(data);

            // Initializing Texture 2
            unsigned int texture2;

            glGenTextures(1, &texture2);
            glBindTexture(GL_TEXTURE_2D, texture2);
            // set the texture wrapping parameters
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	// set texture wrapping to GL_REPEAT (default wrapping method)
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            // set texture filtering parameters
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            // load image, create texture and generate mipmaps
            data = stbi_load("res\\awesomeface.png", &width, &height, &nrChannels, 0);
            if (data)
            {
                // note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(GL_TEXTURE_2D);
            }
            else
            {
                std::cout << "Failed to load texture" << std::endl;
            }
            stbi_image_free(data);

            float mixing = 0;
            ourShader.Enable();
            ourShader.SetUniform1i("texture1", 0);
            ourShader.SetUniform1i("texture2", 1);
            ourShader.SetUniform1f("mixing", mixing);

            // render loop
            // -----------
            while (!win->Closed())
            {
                win->Clear();

                // bind textures on corresponding texture units
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, texture1);

                glActiveTexture(GL_TEXTURE1);
                glBindTexture(GL_TEXTURE_2D, texture2);

                if (input->GetKeyDown(GLFW_KEY_UP))
                {
                    mixing += 0.02;
                    if (mixing > 1)
                        mixing = 1;
                }
                if (input->GetKeyDown(GLFW_KEY_DOWN))
                {
                    mixing -= 0.02;
                    if (mixing < 0)
                        mixing = 0;
                }

                // render container
                ourShader.Enable();
                
                ourShader.SetUniform1f("mixing", mixing);
                glBindVertexArray(VAO);
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

                ourShader.Disable();

                std::cout << "Mixing: " << mixing << std::endl;

                win->Update();
            }
            return 0;
        }

        int Transformations_1()
        {
            Window* win = new Window("Nata Engine", 700, 500);
            Input* input = win->GetInput();

            // build and compile our shader zprogram
            // ------------------------------------
            Shader ourShader("src\\shaders\\transform.vert", "src\\shaders\\transform.frag");

            // set up vertex data (and buffer(s)) and configure vertex attributes
            // ------------------------------------------------------------------
            float vertices[] =
            {
                // positions          // colors           // texture coords
                 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
                 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
                -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
                -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
            };

            unsigned int indices[] =
            {
                0, 1, 3, // first triangle
                1, 2, 3  // second triangle
            };

            unsigned int VBO, VAO, EBO;
            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBO);
            glGenBuffers(1, &EBO);

            glBindVertexArray(VAO);

            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

            // position attribute
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            // color attribute
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
            glEnableVertexAttribArray(1);
            // texture coord attribute
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
            glEnableVertexAttribArray(2);


            // Initializing Texture 1
            unsigned int texture0;
            glGenTextures(1, &texture0);
            glBindTexture(GL_TEXTURE_2D, texture0);
            // set the texture wrapping parameters
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            // set texture filtering parameters
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            // load image, create texture and generate mipmaps
            stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
            int width, height, nrChannels;
            unsigned char* data = stbi_load("res\\awesomeface.png", &width, &height, &nrChannels, 0);
            if (data)
            {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(GL_TEXTURE_2D);
            }
            else
            {
                std::cout << "Failed to load texture" << std::endl;
            }
            stbi_image_free(data);

            ourShader.Enable();
            ourShader.SetUniform1i("texture0", 0);

            while (!win->Closed())
            {
                win->Clear();

                // bind texture on corresponding texture unit
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, texture0);

                if (input->GetKeyDown(GLFW_KEY_UP))
                {
                }
                if (input->GetKeyDown(GLFW_KEY_DOWN))
                {
                }

                // render container
                ourShader.Enable();

                mat4 trans = mat4(1.0f);
                trans = translate(trans, vec3(0.5f, 0.f, 0.f));
                trans = scale(trans, vec3(0.5, 0.5, 0.5));
                trans = rotate(trans, (float)glfwGetTime(), vec3(0.0, 0.0, 1.0));
                ourShader.SetUniformMat4("transform", trans);

                glBindVertexArray(VAO);
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

                trans = mat4(1.0f);
                trans = translate(trans, vec3(-0.5f, 0.f, 0.f));
                
                float scaleAmount = abs(sin((float)glfwGetTime())) + 0.2f;

                trans = scale(trans, vec3(scaleAmount, scaleAmount, 0.5));
                ourShader.SetUniformMat4("transform", trans);

                glBindVertexArray(VAO);
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

                ourShader.Disable();

                win->Update();
            }
            return 0;
        }

        int CoordinateSystems_1()
        {
            Window* win = new Window("OpenGL Studies", 700, 500);
            Input* input = win->GetInput();

            Shader ourShader("src\\shaders\\coordinates.vert", "src\\shaders\\coordinates.frag");

            glm::vec3 cubePos[] = 
            {
                vec3(0.0f,  0.0f,  0.0f),
                vec3(2.0f,  5.0f, -15.0f),
                vec3(-1.5f, -2.2f, -2.5f),
                vec3(-3.8f, -2.0f, -12.3f),
                vec3(2.4f, -0.4f, -3.5f),
                vec3(-1.7f,  3.0f, -7.5f),
                vec3(1.3f, -2.0f, -2.5f),
                vec3(1.5f,  2.0f, -2.5f),
                vec3(1.5f,  0.2f, -1.5f),
                vec3(-1.3f,  1.0f, -1.5f)
            };

            float vertices[] = 
            {
                -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
                 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
                 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
                -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

                -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
                 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
                 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
                 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
                -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
                -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

                -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
                -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
                -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

                 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
                 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
                 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

                -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
                 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
                 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
                -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
                -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

                -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
                 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
                 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
                -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
                -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
            };

            unsigned int VBO, VAO;
            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBO);

            glBindVertexArray(VAO);

            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

            // position attribute
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            // texture coord attribute
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
            glEnableVertexAttribArray(1);


            // Initializing Texture 0
            unsigned int texture0;
            glGenTextures(1, &texture0);
            glBindTexture(GL_TEXTURE_2D, texture0);
            // set the texture wrapping parameters
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            // set texture filtering parameters
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            // load image, create texture and generate mipmaps
            int width, height, nrChannels;
            unsigned char* data = stbi_load("res\\container.jpg", &width, &height, &nrChannels, 0);
            if (data)
            {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(GL_TEXTURE_2D);
            }
            else
            {
                std::cout << "Failed to load texture" << std::endl;
            }
            stbi_image_free(data);

            // Initializing Texture 1
            unsigned int texture1;
            glGenTextures(1, &texture1);
            glBindTexture(GL_TEXTURE_2D, texture1);
            // set the texture wrapping parameters
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            // set texture filtering parameters
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            // load image, create texture and generate mipmaps
            stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
            data = stbi_load("res\\pepega.png", &width, &height, &nrChannels, 0);
            if (data)
            {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(GL_TEXTURE_2D);
            }
            else
            {
                std::cout << "Failed to load texture" << std::endl;
            }
            stbi_image_free(data);

            // View and projection matrices
            glm::mat4 view = glm::mat4(1.0f);
            // note that we're translating the scene in the reverse direction of where we want to move

            glm::mat4 projection;
            projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);


            ourShader.Enable();
            ourShader.SetUniform1i("texture0", 0);
            ourShader.SetUniform1i("texture1", 1);

            glEnable(GL_DEPTH_TEST);

            std::vector<vec3> rotationAxis;
            for (size_t i = 0; i < 10; i++)
            {
                float rx = ((float)rand()) / (float)RAND_MAX;
                float ry = ((float)rand()) / (float)RAND_MAX;
                float rz = ((float)rand()) / (float)RAND_MAX;
                vec3 rv = vec3(rx, ry, rz);
                rotationAxis.push_back(rv);
            }

            view = translate(view, vec3(0.f, 0.f , -3.f));

            float sens = 0.01f;
            while (!win->Closed())
            {
                win->Clear();
                float time = (float)glfwGetTime();

                if (input->GetKeyDown(GLFW_KEY_UP))
                {
                    if (input->GetKeyDown(GLFW_KEY_LEFT_SHIFT))
                        view = translate(view, vec3(0.f, 0.f, 1.f) * sens);
                    else
                        view = translate(view, vec3(0.f, -1.f, 0.f) * sens);
                }

                if (input->GetKeyDown(GLFW_KEY_DOWN))
                {
                    if (input->GetKeyDown(GLFW_KEY_LEFT_SHIFT))
                        view = translate(view, vec3(0.f, 0.f, -1.f) * sens);
                    else
                        view = translate(view, vec3(0.f, 1.f, 0.f) * sens);
                }

                if (input->GetKeyDown(GLFW_KEY_LEFT))
                {
                    view = translate(view, vec3(1.f, 0.f, 0.f) * sens);
                }

                if (input->GetKeyDown(GLFW_KEY_RIGHT))
                {
                    view = translate(view, vec3(-1.f, 0.f, 0.f) * sens);
                }

                ourShader.Enable();
                glBindVertexArray(VAO);

                // bind texture on corresponding texture unit
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, texture0);
                glActiveTexture(GL_TEXTURE1);
                glBindTexture(GL_TEXTURE_2D, texture1);

                ourShader.SetUniformMat4("view", view);
                ourShader.SetUniformMat4("projection", projection);
                for (size_t i = 0; i < 10; i++)
                {
                    mat4 model = mat4(1.0f);

                    vec3 position = vec3(cubePos[i].x, cubePos[i].y/*+ (sin(time) / 2)*/, cubePos[i].z);
                    model = translate(model, position);
                    model = rotate(model, time, rotationAxis[i]);
                    ourShader.SetUniformMat4("model", model);

                    glDrawArrays(GL_TRIANGLES, 0, 36);
                }


                ourShader.Disable();

                win->Update();
            }
            return 0;
        }

        int Camera_1()
        {
            Window* win = new Window("OpenGL Studies", 700, 500);
            Input* input = win->GetInput();

            Shader ourShader("src\\shaders\\coordinates.vert", "src\\shaders\\coordinates.frag");

            glm::vec3 cubePos[] =
            {
                vec3(0.0f,  0.0f,  0.0f),
                vec3(2.0f,  5.0f, -15.0f),
                vec3(-1.5f, -2.2f, -2.5f),
                vec3(-3.8f, -2.0f, -12.3f),
                vec3(2.4f, -0.4f, -3.5f),
                vec3(-1.7f,  3.0f, -7.5f),
                vec3(1.3f, -2.0f, -2.5f),
                vec3(1.5f,  2.0f, -2.5f),
                vec3(1.5f,  0.2f, -1.5f),
                vec3(-1.3f,  1.0f, -1.5f)
            };

            float vertices[] =
            {
                -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
                 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
                 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
                -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

                -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
                 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
                 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
                 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
                -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
                -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

                -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
                -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
                -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

                 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
                 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
                 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

                -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
                 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
                 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
                -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
                -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

                -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
                 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
                 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
                -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
                -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
            };

            unsigned int VBO, VAO;
            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBO);

            glBindVertexArray(VAO);

            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

            // position attribute
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            // texture coord attribute
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
            glEnableVertexAttribArray(1);


            // Initializing Texture 0
            unsigned int texture0;
            glGenTextures(1, &texture0);
            glBindTexture(GL_TEXTURE_2D, texture0);
            // set the texture wrapping parameters
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            // set texture filtering parameters
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            // load image, create texture and generate mipmaps
            int width, height, nrChannels;
            unsigned char* data = stbi_load("res\\container.jpg", &width, &height, &nrChannels, 0);
            if (data)
            {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(GL_TEXTURE_2D);
            }
            else
            {
                std::cout << "Failed to load texture" << std::endl;
            }
            stbi_image_free(data);

            // Initializing Texture 1
            unsigned int texture1;
            glGenTextures(1, &texture1);
            glBindTexture(GL_TEXTURE_2D, texture1);
            // set the texture wrapping parameters
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            // set texture filtering parameters
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            // load image, create texture and generate mipmaps
            stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
            data = stbi_load("res\\pepega.png", &width, &height, &nrChannels, 0);
            if (data)
            {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(GL_TEXTURE_2D);
            }
            else
            {
                std::cout << "Failed to load texture" << std::endl;
            }
            stbi_image_free(data);

            // View and projection matrices
            glm::mat4 view = glm::mat4(1.0f);
            // note that we're translating the scene in the reverse direction of where we want to move

            glm::mat4 projection;
            projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);


            ourShader.Enable();
            ourShader.SetUniform1i("texture0", 0);
            ourShader.SetUniform1i("texture1", 1);

            glEnable(GL_DEPTH_TEST);

            std::vector<vec3> rotationAxis;
            for (size_t i = 0; i < 10; i++)
            {
                float rx = ((float)rand()) / (float)RAND_MAX;
                float ry = ((float)rand()) / (float)RAND_MAX;
                float rz = ((float)rand()) / (float)RAND_MAX;
                vec3 rv = vec3(rx, ry, rz);
                rotationAxis.push_back(rv);
            }

            while (!win->Closed())
            {
                win->Clear();
                float time = (float)glfwGetTime();

                // 1. camera position
                glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);

                // 2. camera direction
                glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, -3.0f);
                glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);

                // 3. right axis
                glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
                glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));

                // 4. up axis
                glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);
                
                float radius = 10.f;
                float camX = sin(time) * radius;
                float camZ = cos(time) * radius;

                cameraPos.x = camX;
                cameraPos.z = camZ;

                view = lookAt(cameraPos, cameraTarget, cameraUp);

                ourShader.Enable();
                glBindVertexArray(VAO);

                // bind texture on corresponding texture unit
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, texture0);
                glActiveTexture(GL_TEXTURE1);
                glBindTexture(GL_TEXTURE_2D, texture1);

                ourShader.SetUniformMat4("view", view);
                ourShader.SetUniformMat4("projection", projection);
                for (size_t i = 0; i < 10; i++)
                {
                    mat4 model = mat4(1.0f);

                    vec3 position = vec3(cubePos[i].x, cubePos[i].y/*+ (sin(time) / 2)*/, cubePos[i].z);
                    model = translate(model, position);
                    model = rotate(model, time, rotationAxis[i]);
                    ourShader.SetUniformMat4("model", model);

                    glDrawArrays(GL_TRIANGLES, 0, 36);
                }


                ourShader.Disable();

                win->Update();
            }
            return 0;
        }

        int Camera_2()
        {
            Window* win = new Window("OpenGL Studies", 700, 500);
            Input* input = win->GetInput();

            Shader ourShader("src\\shaders\\coordinates.vert", "src\\shaders\\coordinates.frag");

            glm::vec3 cubePos[] =
            {
                vec3(0.0f,  0.0f,  0.0f),
                vec3(2.0f,  5.0f, -15.0f),
                vec3(-1.5f, -2.2f, -2.5f),
                vec3(-3.8f, -2.0f, -12.3f),
                vec3(2.4f, -0.4f, -3.5f),
                vec3(-1.7f,  3.0f, -7.5f),
                vec3(1.3f, -2.0f, -2.5f),
                vec3(1.5f,  2.0f, -2.5f),
                vec3(1.5f,  0.2f, -1.5f),
                vec3(-1.3f,  1.0f, -1.5f)
            };

            float vertices[] =
            {
                -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
                 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
                 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
                -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

                -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
                 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
                 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
                 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
                -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
                -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

                -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
                -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
                -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

                 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
                 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
                 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

                -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
                 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
                 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
                -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
                -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

                -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
                 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
                 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
                -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
                -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
            };

            unsigned int VBO, VAO;
            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBO);

            glBindVertexArray(VAO);

            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

            // position attribute
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            // texture coord attribute
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
            glEnableVertexAttribArray(1);


            // Initializing Texture 0
            unsigned int texture0;
            glGenTextures(1, &texture0);
            glBindTexture(GL_TEXTURE_2D, texture0);
            // set the texture wrapping parameters
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            // set texture filtering parameters
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            // load image, create texture and generate mipmaps
            int width, height, nrChannels;
            unsigned char* data = stbi_load("res\\container.jpg", &width, &height, &nrChannels, 0);
            if (data)
            {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(GL_TEXTURE_2D);
            }
            else
            {
                std::cout << "Failed to load texture" << std::endl;
            }
            stbi_image_free(data);

            // Initializing Texture 1
            unsigned int texture1;
            glGenTextures(1, &texture1);
            glBindTexture(GL_TEXTURE_2D, texture1);
            // set the texture wrapping parameters
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            // set texture filtering parameters
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            // load image, create texture and generate mipmaps
            stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
            data = stbi_load("res\\pepega.png", &width, &height, &nrChannels, 0);
            if (data)
            {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(GL_TEXTURE_2D);
            }
            else
            {
                std::cout << "Failed to load texture" << std::endl;
            }
            stbi_image_free(data);

            // View and projection matrices
            glm::mat4 view = glm::mat4(1.0f);
            glm::mat4 projection;
            projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

            ourShader.Enable();
            ourShader.SetUniform1i("texture0", 0);
            ourShader.SetUniform1i("texture1", 1);

            glEnable(GL_DEPTH_TEST);


            std::vector<vec3> rotationAxis;
            for (size_t i = 0; i < 10; i++)
            {
                float rx = ((float)rand()) / (float)RAND_MAX;
                float ry = ((float)rand()) / (float)RAND_MAX;
                float rz = ((float)rand()) / (float)RAND_MAX;
                vec3 rv = vec3(rx, ry, rz);
                rotationAxis.push_back(rv);
            }

            
            const float camSpeed = 2.f;
            const float camSens = 0.2f;
            vec2 lastMousePos = vec2(0.f, 0.f);

            // 1. initial camera position
            float pitch = 0;
            float yaw = -90.f;
            vec3 camPos = glm::vec3(0.f, 0.f, 3.f);
            float deltaTime = 0.f;
            double lastFrame = 0.f;

            while (!win->Closed())
            {
                double currentFrame = glfwGetTime();
                deltaTime = currentFrame - lastFrame;
                lastFrame = currentFrame;

                vec2 mousePos = input->GetMousePos();
                vec2 mouseDelta = vec2(mousePos.x - lastMousePos.x, mousePos.y - lastMousePos.y);
                lastMousePos = mousePos;

                LOGVEC2(mouseDelta.x, mouseDelta.y);

                win->Clear();
                float time = (float)glfwGetTime();

                // 2. camera direction
                pitch += mouseDelta.y * camSens * deltaTime * -1.f;
                yaw += mouseDelta.x * camSens * deltaTime;
                vec3 camForward;
                camForward.x = cos(yaw) * cos(pitch);
                camForward.y = sin(pitch);
                camForward.z = sin(yaw) * cos(pitch);
                camForward = normalize(camForward);

                // 3. right axis
                vec3 camRight = glm::normalize(glm::cross(vec3(0.f, 1.f, 0.f), camForward));

                // 4. up axis
                vec3 camUp = glm::cross(camForward, camRight);

                if (input->GetKeyDown(GLFW_KEY_W))
                {
                    camPos += camSpeed * camForward * deltaTime;
                }
                if (input->GetKeyDown(GLFW_KEY_S))
                {
                    camPos -= camSpeed * camForward * deltaTime;
                }
                if (input->GetKeyDown(GLFW_KEY_A))
                {
                    camPos += camSpeed * camRight * deltaTime;
                }
                if (input->GetKeyDown(GLFW_KEY_D))
                {
                    camPos -= camSpeed * camRight * deltaTime;
                }
                
                view = lookAt(camPos, camPos + camForward, camUp);

                ourShader.Enable();
                glBindVertexArray(VAO);

                // bind texture on corresponding texture unit
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, texture0);
                glActiveTexture(GL_TEXTURE1);
                glBindTexture(GL_TEXTURE_2D, texture1);

                ourShader.SetUniformMat4("view", view);
                ourShader.SetUniformMat4("projection", projection);
                for (size_t i = 0; i < 10; i++)
                {
                    mat4 model = mat4(1.0f);

                    vec3 position = vec3(cubePos[i].x, cubePos[i].y/*+ (sin(time) / 2)*/, cubePos[i].z);
                    model = translate(model, position);
                    model = rotate(model, time, rotationAxis[i]);
                    ourShader.SetUniformMat4("model", model);

                    glDrawArrays(GL_TRIANGLES, 0, 36);
                }


                ourShader.Disable();

                win->Update();
            }
            return 0;
        }

        int Lighting_1()
        {
            Window* win = new Window("OpenGL Studies", 700, 500);
            Input* input = win->GetInput();

            Shader shader("src\\shaders\\lighting.vert", "src\\shaders\\lighting.frag");
            Shader lightShader("src\\shaders\\light_source.vert", "src\\shaders\\light_source.frag");

            float vertices[] =
            {
                -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
                 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
                 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
                 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
                -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
                -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

                -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
                 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
                 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
                 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
                -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
                -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

                -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
                -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
                -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
                -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
                -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
                -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

                 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
                 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
                 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
                 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
                 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
                 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

                -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
                 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
                 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
                 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
                -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
                -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

                -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
                 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
                 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
                 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
                -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
                -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
            };

            // 1. object
            unsigned int VBO, VAO;
            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBO);

            glBindVertexArray(VAO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

            // position attribute
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            // normal attribute
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
            glEnableVertexAttribArray(1);

            // 2. light source
            unsigned int lightVAO;
            glGenVertexArrays(1, &lightVAO);

            glBindVertexArray(lightVAO); 
            // only need to bind buffer; no need to send since vbo already has vertices data that we want
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            // position attribute
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            // normal attribute
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
            glEnableVertexAttribArray(1);

            glEnable(GL_DEPTH_TEST);
            
            // View and projection matrices
            glm::mat4 view = glm::mat4(1.0f);
            glm::mat4 projection;
            projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

            const float camSpeed = 2.f;
            const float camSens = 0.2f;
            vec2 lastMousePos = vec2(0.f, 0.f);

            // 1. initial camera position and rotation
            float pitch = 0.f;
            float yaw = -90.f;
            vec3 camPos = glm::vec3(0.f, 0.f, -3.f);
            float deltaTime = 0.f;
            double lastFrame = 0.f;

            while (!win->Closed())
            {
                double currentFrame = glfwGetTime();
                deltaTime = currentFrame - lastFrame;
                lastFrame = currentFrame;

                win->Clear();
                float time = (float)glfwGetTime();

                // 2. camera forward
                vec3 camForward = vec3(0.f, 0.f, 1.f);

                // 3. right axis
                vec3 camRight = glm::normalize(glm::cross(vec3(0.f, 1.f, 0.f), camForward));

                // 4. up axis
                vec3 camUp = glm::cross(camForward, camRight);

                // handling camera input
                if (input->GetKeyDown(GLFW_KEY_W))
                {
                    camPos += camSpeed * camForward * deltaTime;
                }
                if (input->GetKeyDown(GLFW_KEY_S))
                {
                    camPos -= camSpeed * camForward * deltaTime;
                }
                if (input->GetKeyDown(GLFW_KEY_A))
                {
                    camPos += camSpeed * camRight * deltaTime;
                }
                if (input->GetKeyDown(GLFW_KEY_D))
                {
                    camPos -= camSpeed * camRight * deltaTime;
                }
                
                view = lookAt(camPos, camPos + camForward, camUp);
                

                vec3 lightPosition = vec3(1.2f, 1.f, 2.f);

                // 2. render object
                shader.Enable();
                glBindVertexArray(VAO);
                
                shader.SetUniform3f("objectColor", vec3(1.f, .5f, .31f));
                shader.SetUniform3f("lightColor", vec3(1.f, 1.f, 1.f));
                shader.SetUniform3f("lightPos", lightPosition);

                shader.SetUniformMat4("view", view);
                shader.SetUniformMat4("projection", projection);

                vec3 position = vec3(0.f, 0.f, 0.f);
                mat4 model = mat4(1.0f);
                model = translate(model, position);
                //model = rotate(model, time, vec3(.5f, 1.f, 0.f));
                shader.SetUniformMat4("model", model);

                glDrawArrays(GL_TRIANGLES, 0, 36);

                // 2. render light source
                lightShader.Enable();
                glBindVertexArray(lightVAO);

                lightShader.SetUniformMat4("view", view);
                lightShader.SetUniformMat4("projection", projection);

                model = mat4(1.0f);
                model = translate(model, lightPosition);
                model = scale(model, vec3(0.2f));
                lightShader.SetUniformMat4("model", model);

                glDrawArrays(GL_TRIANGLES, 0, 36);

                lightShader.Disable();

                win->Update();
            }
            return 0;
        }
	}
}