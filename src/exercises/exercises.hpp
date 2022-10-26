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
                shader->SetUniform2f("Offset", Vector2(1.f, 1.f));


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
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            // set texture filtering parameters
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
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

            ourShader.Enable();
            ourShader.SetUniform1i("texture1", 0);
            ourShader.SetUniform1i("texture2", 1);

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

                // render container
                ourShader.Enable();
                glBindVertexArray(VAO);
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

                win->Update();
            }
            return 0;
        }
	}
}