#version 330

// Input
in vec3 world_position;
in vec3 world_normal;

// Uniforms for light properties
uniform vec3 light_direction;
uniform vec3 light_position;
uniform vec3 eye_position;

uniform vec3 light_pos2;

uniform float material_kd;
uniform float material_ks;
uniform int material_shininess;
uniform float cut_off;

// TODO(student): Declare any other uniforms

uniform vec3 object_color;
uniform int is_spotlight;

// Output
layout(location = 0) out vec4 out_color;


void main()
{
    // TODO(student): Define ambient, diffuse and specular light components
    vec3 L = normalize( light_position - world_position );
    vec3 V = normalize( eye_position - world_position );
    vec3 H = normalize( L + V );

    float ambient_light = 0.25;
    float diffuse_light = material_kd * max (dot(world_normal,L), 0);
    vec3 R = reflect (-L, world_normal);
    float specular_light = 0;
    // It's important to distinguish between "reflection model" and
    // "shading method". In this shader, we are experimenting with the Phong
    // (1975) and Blinn-Phong (1977) reflection models, and we are using the
    // Phong (1975) shading method. Don't mix them up!
    if (diffuse_light > 0)
    {
        specular_light = material_ks * pow(max(dot(V, R), 0), material_shininess);
    }

    // TODO(student): If (and only if) the light is a spotlight, we need to do
    // some additional things.

//    cut_off = radians(30.0f);
    float spot_light = dot(-L, light_direction);
    float spot_light_limit = cos(cut_off);

    float linear_att = (spot_light - spot_light_limit) / (1.0f - spot_light_limit);
    float light_att_factor = pow(distance(world_position, light_position),-2);

    if (is_spotlight == 1) {
        if (spot_light > spot_light_limit) {
            light_att_factor *= pow(linear_att, 2);
        } else {
            light_att_factor = 0;
        }
    }
    // TODO(student): Compute the total light. You can just add the components
    // together, but if you're feeling extra fancy, you can add individual
    // colors to the light components. To do that, pick some vec3 colors that
    // you like, and multiply them with the respective light components.
    vec3 c = 0 + vec3(ambient_light) +  light_att_factor * ( diffuse_light + specular_light) * vec3(1,0,0);

    // TODO(student): Write pixel out color
    out_color = vec4(object_color * c, 1);

    // TODO(student): Define ambient, diffuse and specular light components
    L = normalize( light_pos2 - world_position );
     V = normalize( eye_position - world_position );
     H = normalize( L + V );

     ambient_light = 0.25;
     diffuse_light = material_kd * max (dot(world_normal,L), 0);
     R = reflect (-L, world_normal);
     specular_light = 0;
    // It's important to distinguish between "reflection model" and
    // "shading method". In this shader, we are experimenting with the Phong
    // (1975) and Blinn-Phong (1977) reflection models, and we are using the
    // Phong (1975) shading method. Don't mix them up!
    if (diffuse_light > 0)
    {
        specular_light = material_ks * pow(max(dot(V, R), 0), material_shininess);
    }

    // TODO(student): If (and only if) the light is a spotlight, we need to do
    // some additional things.

//     cut_off = radians(30.0f);
     spot_light = dot(-L, light_direction);
     spot_light_limit = cos(cut_off);

     linear_att = (spot_light - spot_light_limit) / (1.0f - spot_light_limit);
     light_att_factor = pow(distance(world_position, light_pos2),-2);

//    if (is_spotlight == 1) {
//        if (spot_light > spot_light_limit) {
//            light_att_factor *= pow(linear_att, 2);
//        } else {
//            light_att_factor = 0;
//        }
//    }
    // TODO(student): Compute the total light. You can just add the components
    // together, but if you're feeling extra fancy, you can add individual
    // colors to the light components. To do that, pick some vec3 colors that
    // you like, and multiply them with the respective light components.
     c = 0 +  light_att_factor * ( diffuse_light + specular_light) * vec3(0,0,1);


    // TODO(student): Write pixel out color
    out_color += vec4(object_color * c, 0);

}
