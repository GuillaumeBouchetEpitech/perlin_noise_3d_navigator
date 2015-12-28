#include "t_shader_perlin3d.h"


#include <QFile>
#include <QDebug>


void    t_Shader_Perlin3D::init()
{

    // if ( this->isAvailable_shader100() )
        this->prepareShaderProgram( "shaders/test_100.vert.c", "shaders/test_100.frag.c" );

    /**/
    // else // if ( isAvailable_shader150() )
        // this->prepareShaderProgram( "shaders/test_150.vert", "shaders/test_150.frag" );
    //*/


    _location_a_vertex = glGetAttribLocation( _programm_id, "a_vertex" );
    _location_a_color = glGetAttribLocation( _programm_id, "a_color" );
    _location_a_normal = glGetAttribLocation( _programm_id, "a_normal" );

    _location_u_modelviewMatrix = glGetUniformLocationARB( _programm_id, "u_modelviewMatrix" );
    _location_u_projectionMatrix = glGetUniformLocationARB( _programm_id, "u_projectionMatrix" );
    _location_u_mode = glGetUniformLocationARB( _programm_id, "u_mode" );
    _location_u_lightEnabled = glGetUniformLocationARB( _programm_id, "u_lightEnabled" );

    glUniform1i(  _location_u_lightEnabled, 1 );

    glCheckError();
}


bool    t_Shader_Perlin3D::isAvailable_shader100()
{
    return ( GLEW_ARB_shading_language_100 &&
             GLEW_ARB_shader_objects       &&
             GLEW_ARB_vertex_shader        &&
             GLEW_ARB_fragment_shader );
}

/**
bool    t_Shader_Perlin3D::isAvailable_shader150()
{
    return ( GLEW_ARB_shading_language_150 &&
             GLEW_ARB_shader_objects       &&
             GLEW_ARB_vertex_shader        &&
             GLEW_ARB_fragment_shader );
}
//*/


void    t_Shader_Perlin3D::prepareShaderProgram( const std::string& vertexShaderPath,
                                                 const std::string& fragmentShaderPath )
{
    struct  Shader
    {
        const std::string&  filename;
        GLenum              type;
        GLchar*             source;
    } shaders[2] = {
        { vertexShaderPath, GL_VERTEX_SHADER, NULL },
        { fragmentShaderPath, GL_FRAGMENT_SHADER, NULL }
    };


    GLuint program = glCreateProgram();

    for ( int i = 0; i < 2; ++i )
    {
        Shader& s = shaders[i];
        QFile file( s.filename.c_str() );

        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            std::cerr
                    << "[F:" << __FILE__ << "]"
                    << "[f:" << __func__ << "]"
                    << "[l:" << __LINE__ << "]"

                    << "Cannot open file " << s.filename << std::endl;
            exit( EXIT_FAILURE );
        }
        QByteArray data = file.readAll();
        file.close();
        s.source = data.data();

        if ( shaders[i].source == NULL )
        {
            std::cerr
                    << "[F:" << __FILE__ << "]"
                    << "[f:" << __func__ << "]"
                    << "[l:" << __LINE__ << "]"

                    << "Failed to read " << s.filename << std::endl;
            exit( EXIT_FAILURE );
        }

        GLuint shader = glCreateShader( s.type );
        glShaderSource( shader, 1, (const GLchar**) &s.source, NULL );
        glCompileShader( shader );

        GLint  compiled;
        glGetShaderiv( shader, GL_COMPILE_STATUS, &compiled );

        if ( !compiled )
        {
            std::cerr
                    << "[F:" << __FILE__ << "]"
                    << "[f:" << __func__ << "]"
                    << "[l:" << __LINE__ << "]"

                    << s.filename << " failed to compile:" << std::endl;

            GLint  logSize;
            glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &logSize );
            char* logMsg = new char[logSize];
            glGetShaderInfoLog( shader, logSize, NULL, logMsg );
            qWarning() << logMsg;
            delete [] logMsg;

            exit( EXIT_FAILURE );
        }

        glAttachShader( program, shader );
    }

    /* Link output */
    glBindFragDataLocation(program, 0, "fragColor");

    /* link  and error check */
    glLinkProgram(program);

    GLint  linked;
    glGetProgramiv( program, GL_LINK_STATUS, &linked );

    if ( !linked )
    {
        qWarning() << "Shader program failed to link";
        GLint  logSize;
        glGetProgramiv( program, GL_INFO_LOG_LENGTH, &logSize);
        char* logMsg = new char[logSize];
        glGetProgramInfoLog( program, logSize, NULL, logMsg );
        qWarning() << logMsg ;
        delete [] logMsg;

        exit( EXIT_FAILURE );
    }

    /* use program object */
    glUseProgram(program);

    glCheckError();

    _programm_id = program;

    //return program;
}

