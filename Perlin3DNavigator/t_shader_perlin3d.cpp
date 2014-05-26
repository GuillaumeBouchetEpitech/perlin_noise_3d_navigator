#include "t_shader_perlin3d.h"


#include <QFile>
#include <QDebug>


void    t_Shader_Perlin3D::init()
{

    glCheckError();


    //if ( this->isAvailable_shader100() )
        this->prepareShaderProgram( "shaders/test_100.vert", "shaders/test_100.frag" );

    /**
    else if ( isAvailable_shader150() )
        this->prepareShaderProgram( "shaders/test_150.vert", "shaders/test_150.frag" );
    //*/


    glCheckError();

    _location_a_vertex = glGetAttribLocation( _programm_id, "a_vertex" );
    _location_a_color = glGetAttribLocation( _programm_id, "a_color" );
    _location_a_normal = glGetAttribLocation( _programm_id, "a_normal" );
    _location_u_modelviewMatrix = glGetUniformLocationARB( _programm_id, "u_modelviewMatrix" );
    _location_u_projectionMatrix = glGetUniformLocationARB( _programm_id, "u_projectionMatrix" );
    _location_u_normalMatrix = glGetUniformLocationARB( _programm_id, "u_normalMatrix" );
    _location_u_mode = glGetUniformLocationARB( _programm_id, "u_mode" );

    _location_u_lightEnabled = glGetUniformLocationARB( _programm_id, "u_lightEnabled" );
    glUniform1i(  _location_u_lightEnabled, 1 );

    _location_u_advance = glGetUniformLocationARB( _programm_id, "u_advance" );
    glUniform1f( _location_u_advance, 0.0f );

    _location_u_perturbationEnabled = glGetUniformLocationARB( _programm_id, "u_perturbationEnabled" );
    glUniform1i( _location_u_perturbationEnabled, 0 );


    _locations_light.directionLocation = glGetUniformLocation( _programm_id, "u_light.direction");
    _locations_light.ambientColorLocation = glGetUniformLocation( _programm_id, "u_light.ambientColor");
    _locations_light.diffuseColorLocation = glGetUniformLocation( _programm_id, "u_light.diffuseColor");
    _locations_light.specularColorLocation = glGetUniformLocation( _programm_id, "u_light.specularColor");

    _locations_material.ambientColorLocation = glGetUniformLocation( _programm_id, "u_material.ambientColor");
    _locations_material.diffuseColorLocation = glGetUniformLocation( _programm_id, "u_material.diffuseColor");
    _locations_material.specularColorLocation = glGetUniformLocation( _programm_id, "u_material.specularColor");
    _locations_material.specularExponentLocation = glGetUniformLocation( _programm_id, "u_material.specularExponent");


    _properties_light.direction = myGL::Vec3f(1,1,1);
    _properties_light.ambientColor = myGL::Vec4f(0.3f,0.3f,0.3f, 1.0f);
    _properties_light.diffuseColor = myGL::Vec4f(1.0f,1.0f,1.0f, 1.0f);
    _properties_light.specularColor = myGL::Vec4f(1.0f,1.0f,1.0f, 1.0f);

    _properties_material.ambientColor = myGL::Vec4f(1.0f,1.0f,1.0f, 1.0f);
    _properties_material.diffuseColor = myGL::Vec4f(1.0f,1.0f,1.0f, 1.0f);
    _properties_material.specularColor = myGL::Vec4f(1.0f,1.0f,1.0f, 1.0f);
    _properties_material.specularExponent = 20.0f;
    //_locations_material.specularExponent = 1.0f;

    myGL::normalize( _properties_light.direction );
    glUniform3fv( _locations_light.directionLocation, 1,     &(_properties_light.direction.x) );

    glUniform4fv( _locations_light.ambientColorLocation, 1,  &(_properties_light.ambientColor.x) );
    glUniform4fv( _locations_light.diffuseColorLocation, 1,  &(_properties_light.diffuseColor.x) );
    glUniform4fv( _locations_light.specularColorLocation, 1, &(_properties_light.specularColor.x) );

    glUniform4fv( _locations_material.ambientColorLocation, 1,  &(_properties_material.ambientColor.x) );
    glUniform4fv( _locations_material.diffuseColorLocation, 1,  &(_properties_material.diffuseColor.x) );
    glUniform4fv( _locations_material.specularColorLocation, 1, &(_properties_material.specularColor.x) );
    glUniform1f(  _locations_material.specularExponentLocation, _properties_material.specularExponent );

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
    glCheckError();

    struct  Shader
    {
        const std::string&  filename;
        GLenum              type;
        GLchar*             source;
    } shaders[2] =
    {
        //    { vertexShaderPath.c_str(), GL_VERTEX_SHADER, NULL },
        //    { fragmentShaderPath.c_str(), GL_FRAGMENT_SHADER, NULL }
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

