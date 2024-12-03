
#include "Object3dSkinning.hlsli"

ConstantBuffer<Material> gMaterial : register(b0);
ConstantBuffer<PunctualLight> gPunctualLight : register(b1);
ConstantBuffer<Camera> gCamera : register(b2);
ConstantBuffer<ModelMaterial> gModelMaterial : register(b3);
Texture2D<float32_t4> gTexture : register(t0);
SamplerState gSampler : register(s0);


PixelShaderOutput main(VertexShaderOutput input)
{
    PixelShaderOutput output;
    
    float4 transformedUV = mul(float4(input.texcoord, 0.0f, 1.0f), mul(gMaterial.uvTransform, gModelMaterial.uvTransform));

    float32_t4 textureColor = gTexture.Sample(gSampler, transformedUV.xy);

    float32_t3 toEye = normalize(gCamera.worldPosition - input.worldPosition);
    
    // DirectionalLight    
    float32_t3 halfVector = normalize(-gPunctualLight.directionalLight.direction + toEye);
    float NDotH = dot(normalize(input.normal), halfVector);
    float specularPow = 0.0f;

    // PointLight
    float32_t3 pointLightDirection = normalize(input.worldPosition - gPunctualLight.pointLight.position);
    float32_t pointLightDistance = length(gPunctualLight.pointLight.position - input.worldPosition);
    float32_t pointLightFactor = pow(saturate(-pointLightDistance / gPunctualLight.pointLight.radius + 1.0), gPunctualLight.pointLight.decay);
    float32_t3 halfVectorPointLight = normalize(-pointLightDirection + toEye);
    float NDotHPoint = dot(normalize(input.normal), halfVectorPointLight);
    float specularPowPointLight = 0.0f;

    // SpotLight
    float32_t3 spotLightDirectionOnSurface = normalize(input.worldPosition - gPunctualLight.spotLight.position);
    float32_t spotLightDistance = length(gPunctualLight.spotLight.position - input.worldPosition);
    float32_t spotLightAttenuationFactor = pow(saturate(-spotLightDistance / gPunctualLight.spotLight.distance + 1.0f), gPunctualLight.spotLight.decay);
    
    float32_t3 spotLightHalfVector = normalize(-spotLightDirectionOnSurface + toEye);
    float spotLightNDotH = dot(normalize(input.normal), spotLightHalfVector);
    float specularPowSpotLight = 0.0f;

    float32_t cosAngle = dot(spotLightDirectionOnSurface, gPunctualLight.spotLight.direction);
    float32_t falloffFactor = saturate((cosAngle - gPunctualLight.spotLight.cosAngle) / (gPunctualLight.spotLight.cosFalloffStart - gPunctualLight.spotLight.cosAngle));
    
    // Texture��a�̒l��0.5�ȉ��̎���Pixel��p�p
    if (textureColor.a <= 0.5)
    {
        discard;
    }

    if (gMaterial.enbleLighting != 0)
    {
        if (gMaterial.shininess >= 1.0f)
        {
            // ���ʔ��˂̌v�Z
            specularPow = pow(saturate(NDotH), gMaterial.shininess);
            specularPowPointLight = pow(saturate(NDotHPoint), gMaterial.shininess);
            specularPowSpotLight = pow(saturate(spotLightNDotH), gMaterial.shininess);
        }

        // DirectionLight
        float nDotL = dot(normalize(input.normal), -gPunctualLight.directionalLight.direction);
        float cos = pow(nDotL * 0.5f + 0.5f, 2.0f);
        // PointLight
        float pointnDotL = dot(normalize(input.normal), -pointLightDirection);
        float cosPointLight = pow(pointnDotL * 0.5f + 0.5f, 2.0f);
        // SpotLight
        float spotLightnDotL = dot(normalize(input.normal), -spotLightDirectionOnSurface);
        float spotLightCos = pow(spotLightnDotL * 0.5f + 0.5f, 2.0f);
        
        // �g�U����
        // DirectionalLight
        float32_t3 diffuseDirectionalLight =
        gModelMaterial.color.rgb * gMaterial.color.rgb * textureColor.rgb * gPunctualLight.directionalLight.color.rgb * cos * gPunctualLight.directionalLight.intensity;
        // PointLight
        float32_t3 diffusePointLight =
        gModelMaterial.color.rgb * gMaterial.color.rgb * textureColor.rgb * gPunctualLight.pointLight.color.rgb * cosPointLight * gPunctualLight.pointLight.intensity * pointLightFactor;
        // SpotLight
        float32_t3 diffuseSpotLight =
        gModelMaterial.color.rgb * gMaterial.color.rgb * textureColor.rgb * gPunctualLight.spotLight.color.rgb * spotLightCos * gPunctualLight.spotLight.intensity * spotLightAttenuationFactor * falloffFactor;
        
        // ���ʔ���
        // DirectionalLight
        float32_t3 specularDirectionalLight = gPunctualLight.directionalLight.color.rgb * gPunctualLight.directionalLight.intensity * specularPow * float32_t3(1.0f, 1.0f, 1.0f);
        // PointLight
        float32_t3 specularPointLight = gPunctualLight.pointLight.color.rgb * gPunctualLight.pointLight.intensity * pointLightFactor * specularPowPointLight * float32_t3(1.0f, 1.0f, 1.0f);
        // SpotLight
        float32_t3 specularSpotLight = gPunctualLight.spotLight.color.rgb * gPunctualLight.spotLight.intensity * spotLightAttenuationFactor * falloffFactor * specularPowSpotLight * float32_t3(1.0f, 1.0f, 1.0f);
        
        // �g�U���ˁA���ʔ���
        output.color.rgb = diffuseDirectionalLight + specularDirectionalLight + diffusePointLight + specularPointLight + diffuseSpotLight + specularSpotLight;
        
        // �A���t�@�l�͍��܂Œʂ�
        output.color.a = gModelMaterial.color.a * gMaterial.color.a * textureColor.a;
   
    }
    else
    {
        output.color = gModelMaterial.color * gMaterial.color * textureColor;
    }
    
    // output.color��a�l��0�̎���Pixel��p�p
    if (output.color.a == 0.0)
    {
        discard;
    }
    
    return output;
}