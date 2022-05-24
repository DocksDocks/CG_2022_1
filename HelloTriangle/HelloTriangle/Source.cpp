/* Hello Triangle - código adaptado de https://learnopengl.com/#!Getting-started/Hello-Triangle 
 *
 * Código inicial para trabalhar com OpenGL 4
 * Adaptado pelos professores Vinicius Cassol e Rossana Queiroz
 * para uso didático em sala de aula
 * 
 */

#include <iostream>
#include <string>
#include <assert.h>

using namespace std;

//Dependêncais - "OpenGL Friends"
// GLAD
#include <glad/glad.h>	
// GLFW
#include <GLFW/glfw3.h>


// Protótipo da função de callback de teclado
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// Protótipos das funções
int setupShader();
int setupGeometry();

// Dimensões da janela (pode ser alterado em tempo de execução)
const GLuint WIDTH = 800, HEIGHT = 600;

// Código fonte do Vertex Shader (em GLSL): ainda hardcoded
const GLchar* vertexShaderSource = "#version 450\n"
"layout (location = 0) in vec3 position;\n"
"void main()\n"
"{\n"
//...pode ter mais linhas de código aqui!
"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
"}\0";

//Códifo fonte do Fragment Shader (em GLSL): ainda hardcoded
const GLchar* fragmentShaderSource = "#version 450\n"
"uniform vec4 inputColor;\n"
"out vec4 color;\n"
"void main()\n"
"{\n"
"color = inputColor;\n"
"}\n\0";

// Função MAIN
int main()
{
	// Inicialização da GLFW
	glfwInit();

	//Muita atenção aqui: alguns ambientes não aceitam essas configurações
	//Você deve adaptar para a versão do OpenGL suportada por sua placa
	//Sugestão: comente essas linhas de código para desobrir a versão e
	//depois atualize (por exemplo: 4.5 com 4 e 5)
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Essencial para computadores da Apple
//#ifdef __APPLE__
//	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//#endif

	// Criação da janela GLFW
		GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Pressione A - B - D ou E para navegar", nullptr, nullptr); // modificado a aba do triangulo
	glfwMakeContextCurrent(window);

	// Fazendo o registro da função de callback para a janela GLFW
	glfwSetKeyCallback(window, key_callback);

	// GLAD: carrega todos os ponteiros de funções da OpenGL
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;

	}

	// Obtendo as informações de versão
	const GLubyte* renderer = glGetString(GL_RENDERER); /* get renderer string */
	const GLubyte* version = glGetString(GL_VERSION); /* version as a string */
	cout << "Renderer: " << renderer << endl;
	cout << "OpenGL version supported " << version << endl;

	// Definindo as dimensões da viewport com as mesmas dimensões da janela da aplicação
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);


	// Compilando e buildando o programa de shader
	GLuint shaderID = setupShader();

	// Gerando um buffer simples, com a geometria de um triângulo
	GLuint VAO = setupGeometry();
	

	// Enviando a cor desejada (vec4) para o fragment shader
	// Utilizamos a variáveis do tipo uniform em GLSL para armazenar esse tipo de info
	// que não está nos buffers
	GLint colorLoc = glGetUniformLocation(shaderID, "inputColor");
	assert(colorLoc > -1);
	
	glUseProgram(shaderID);
	

	// Loop da aplicação - "game loop"
	while (!glfwWindowShouldClose(window))
	{
		// Checa se houveram eventos de input (key pressed, mouse moved etc.) e chama as funções de callback correspondentes
		glfwPollEvents();

		bool a = glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS;
		bool b = glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS;
		bool d = glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS;
		bool e = glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS;
		
		//6.Faça o desenho de um círculo na tela, utilizando a equação paramétrica do círculo para gerar os vértices.Depois disso :
		//a)Desenhe um octágono
		//COMPLETO
		if (a) {
			glLineWidth(15);
			glClearColor(1.0f, 1.0f, 1.0f, 1.0f); //cor de fundo
			glClear(GL_COLOR_BUFFER_BIT);
			glUniform4f(colorLoc, 0.0f, 0.0f, 1.0f, 1.0f); //enviando cor para variável uniform inputColor
			glDrawArrays(GL_TRIANGLE_FAN, 0, 8);
			glBindVertexArray(VAO);
		}

		//b)Desenhe um pentágono
		if (b) {
			glClear(GL_COLOR_BUFFER_BIT);
			glLineWidth(15);
			glUniform4f(colorLoc, 1.0f, 0.0f, 1.0f, 1.0f); //enviando cor para variável uniform inputColor
			glDrawArrays(GL_TRIANGLE_FAN, 8, 5);
			glBindVertexArray(VAO);
		}
		/*d)Desenhe uma fatia de pizza*/
		if (d) {
			glClear(GL_COLOR_BUFFER_BIT);
			glLineWidth(15);
			glUniform4f(colorLoc, 1.0f, 1.0f, 0.0f, 1.0f);
			glDrawArrays(GL_TRIANGLE_FAN, 13, 21);
		}
		//e)Desenhe uma “estrela”
		//glClearColor(1.0f, 1.0f, 1.0f, 1.0f); //cor de fundo
		if (e) {
			glClear(GL_COLOR_BUFFER_BIT);
			glLineWidth(30);
			glClear(GL_COLOR_BUFFER_BIT);
			glUniform4f(colorLoc, 0.0f, 0.0f, 1.0f, 1.0f); //enviando cor para variável uniform inputColor
			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLES, 34, 15);
			glUniform4f(colorLoc, 1.0f, 0.0f, 0.0f, 1.0f); //enviando cor para variável uniform inputColor
			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLE_FAN, 49, 5);
		}
		/*
		if(glwGetKey(window,GLFW_KEY_A) == GLFW_PRESS)
			//codigo da a)
		if(glwGetKey(window,GLFW_KEY_B) == GLFW_PRESS)
			//codigo da b)
		if(glwGetKey(window,GLFW_KEY_C) == GLFW_PRESS)
			//codigo da c)
		if(glwGetKey(window,GLFW_KEY_E) == GLFW_PRESS)
			//codigo da e)
			*/
		// Troca os buffers da tela
		glfwSwapBuffers(window);
	}
	// Pede pra OpenGL desalocar os buffers
	glDeleteVertexArrays(1, &VAO);
	// Finaliza a execução da GLFW, limpando os recursos alocados por ela
	glfwTerminate();
	return 0;
}

// Função de callback de teclado - só pode ter uma instância (deve ser estática se
// estiver dentro de uma classe) - É chamada sempre que uma tecla for pressionada
// ou solta via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

//Esta função está basntante hardcoded - objetivo é compilar e "buildar" um programa de
// shader simples e único neste exemplo de código
// O código fonte do vertex e fragment shader está nos arrays vertexShaderSource e
// fragmentShader source no iniçio deste arquivo
// A função retorna o identificador do programa de shader
int setupShader()
{
	// Vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	// Checando erros de compilação (exibição via log no terminal)
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// Fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	// Checando erros de compilação (exibição via log no terminal)
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// Linkando os shaders e criando o identificador do programa de shader
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	// Checando por erros de linkagem
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return shaderProgram;
}

// Esta função está bastante harcoded - objetivo é criar os buffers que armazenam a 
// geometria de um triângulo
// Apenas atributo coordenada nos vértices
// 1 VBO com as coordenadas, VAO com apenas 1 ponteiro para atributo
// A função retorna o identificador do VAO
int setupGeometry()
{
	// Aqui setamos as coordenadas x, y e z do triângulo e as armazenamos de forma
	// sequencial, já visando mandar para o VBO (Vertex Buffer Objects)
	// Cada atributo do vértice (coordenada, cores, coordenadas de textura, normal, etc)
	// Pode ser arazenado em um VBO único ou em VBOs separados
	GLfloat vertices[] = {
		//6-A OCTAGONO - COMPLETO // 8
		0.51f, 0.77f, 0.0f,
		0.7f, 0.77f, 0.0f,
		0.83f, 0.63f, 0.0f,
		0.83f, 0.43f, 0.0f,
		0.7f, 0.29f, 0.0f,
		0.51f, 0.29f, 0.0f,
		0.38f, 0.43f, 0.0f,
		0.38f, 0.63f, 0.0f,
		//6-B PENTAGONO - COMPLETO // 8 + 5
		-0.6f, -0.2f, 0.0f,// a
		-0.35f, -0.36f, 0.0f,//b
		-0.4f, -0.65f, 0.0f,//c
		-0.8f, -0.65f, 0.0f,//d
		-0.85f, -0.36f, 0.0f,//e
		// 6-D - Fatia de Pizza 1 + 20
		0.0f, 0.0f, 0.0f,
		//1par
		-0.25f, 0.42f, 0.0f,
		-0.25f, 0.40f, 0.0f,
		//2par
		-0.25f, 0.4f, 0.0f,
		-0.1875f, 0.42f, 0.0f,
		//3par
		-0.1875f, 0.42f, 0.0f,
		-0.125f, 0.44f, 0.0f,
		//4par
		-0.125f, 0.44f, 0.0f,
		-0.0625f, 0.46f, 0.0f,
		//5par
		-0.0625f, 0.46f, 0.0f,
		0.0f, 0.48f, 0.0f,
		//6par
		0.0f, 0.48f, 0.0f,
		0.0625f, 0.48f, 0.0f,
		//7par
		0.0625f, 0.48f, 0.0f,
		0.125f, 0.46f, 0.0f,
		//8par
		0.125f, 0.46f, 0.0f,
		0.1875f, 0.44f, 0.0f,
		//9par
		0.1875f, 0.44f, 0.0f,
		0.25f, 0.42f, 0.0f,
		//10 par
		0.25f, 0.42f, 0.0f,
		0.25f, 0.40f, 0.0f,

		/*ESTRELA 6 - E) COMPLETO*/
		//Primeiro Triangulo
		-0.60f, 0.77f, 0.0f, //35
		-0.42f, 0.77f, 0.0f,
		-0.58f, 0.68f, 0.0f,
		//Segundo Triangulo
		-0.64f, 1.00f, 0.0f, //38
		-0.68f, 0.77f, 0.0f,
		-0.60f, 0.77f, 0.0f,
		//Terceiro Triangulo
		-0.68f, 0.77f, 0.0f, //41
		-0.70f, 0.68f, 0.0f,
		-0.86f, 0.77f, 0.0f,
		//Quarto Triangulo
		-0.64f, 0.63f, 0.0f, //44
		-0.70f, 0.68f, 0.0f,
		-0.82f, 0.43f, 0.0f,
		//Quinto Triangulo
		-0.64f, 0.63f, 0.0f, //47
		-0.58f, 0.68f, 0.0f,
		-0.51f, 0.43f, 0.0f,
		//pentagono - triangle fan
		-0.60f, 0.77f, 0.0f,
		-0.68f, 0.77f, 0.0f,
		-0.70f, 0.68f, 0.0f,
		-0.64f, 0.63f, 0.0f,
		-0.58f, 0.68f, 0.0f
		//FIM ESTRELA
	};

	GLuint VBO, VAO;

	//Geração do identificador do VBO
	glGenBuffers(1, &VBO);
	//Faz a conexão (vincula) do buffer como um buffer de array
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//Envia os dados do array de floats para o buffer da OpenGl
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//Geração do identificador do VAO (Vertex Array Object)
	glGenVertexArrays(1, &VAO);
	// Vincula (bind) o VAO primeiro, e em seguida  conecta e seta o(s) buffer(s) de vértices
	// e os ponteiros para os atributos 
	glBindVertexArray(VAO);
	//Para cada atributo do vertice, criamos um "AttribPointer" (ponteiro para o atributo), indicando: 
	// Localização no shader * (a localização dos atributos devem ser correspondentes no layout especificado no vertex shader)
	// Numero de valores que o atributo tem (por ex, 3 coordenadas xyz) 
	// Tipo do dado
	// Se está normalizado (entre zero e um)
	// Tamanho em bytes 
	// Deslocamento a partir do byte zero 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// Observe que isso é permitido, a chamada para glVertexAttribPointer registrou o VBO como o objeto de buffer de vértice 
	// atualmente vinculado - para que depois possamos desvincular com segurança
	glBindBuffer(GL_ARRAY_BUFFER, 0); 

	// Desvincula o VAO (é uma boa prática desvincular qualquer buffer ou array para evitar bugs medonhos)
	glBindVertexArray(0); 

	return VAO;
}

