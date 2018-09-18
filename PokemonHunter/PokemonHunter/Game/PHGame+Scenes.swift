//
//  PHGame+Scenes.swift
//  PokemonHunter
//
//  Created by Renaud Buisine on 09/09/2018.
//  Copyright © 2018 Renaud Buisine. All rights reserved.
//

import PokeEngine_iOS
import SpriteKit
import GameplayKit

extension PHGame {
    func sceneFrom(_ scene: PokeMapScene) -> PHScene? {
        let phScene = GKScene(fileNamed: "MapScene")?.rootNode as? PHMapScene
        phScene?.pokeScene = scene
        phScene?.resourceContainer = PHDefaultMapResourceContainer()
        return phScene
    }
    //defaults - should not happen
    func sceneFrom(_ scene: PokeScene) -> PHScene? {
        return nil
    }
}

extension PHGame: PHSceneDelegate {
    func sceneDidLoad(_ scene: PHScene) {
        
    }
}
