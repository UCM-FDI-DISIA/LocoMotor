Scene = {
    MainCamera = {
        Camera = {},
        AudioListener = {}
    },
    Object = {
        AudioSource = {
            Volume = 1,
            PlayOnAwake = "Assets/Sounds/prueba.wav"
        }
    },
    Emitter = {
        EventEmitter = {
            EventID = "event:/Music/Level 02",
            Play = "";
        }
    },
    cube = {
        Transform = {
            position = "0 0 -150",
            size = "20 20 20",
            rotation = "15 -40 0"
        },
        MeshRenderer = {
            mesh = "CubemanMesh.mesh",
            material = "CustomMaterial"
        }
    }
}