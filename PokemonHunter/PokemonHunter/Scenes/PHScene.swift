//
//  GameScene.swift
//  PokemonHunter
//
//  Created by Renaud Buisine on 04/09/2018.
//  Copyright © 2018 Renaud Buisine. All rights reserved.
//

import SpriteKit
import GameplayKit
import PokeEngine_iOS

class PHScene: SKScene {
    
    var control: PHControl?
    var resourceContainer: PHResourceContainer?
    var pokeScene: PokeScene?
    
//MARK: - Touches
    override func touchesBegan(_ touches: Set<UITouch>, with event: UIEvent?) {
        guard let control = control else {
            return
        }
        for t in touches { control.touchDown(atPoint: t.location(in: self)) }
    }
    
    override func touchesMoved(_ touches: Set<UITouch>, with event: UIEvent?) {
        guard let control = control else {
            return
        }
        for t in touches { control.touchMoved(toPoint: t.location(in: self)) }
    }
    
    override func touchesEnded(_ touches: Set<UITouch>, with event: UIEvent?) {
        guard let control = control else {
            return
        }
        for t in touches { control.touchUp(atPoint: t.location(in: self)) }
    }
    
    override func touchesCancelled(_ touches: Set<UITouch>, with event: UIEvent?) {
        guard let control = control else {
            return
        }
        for t in touches { control.touchUp(atPoint: t.location(in: self)) }
    }
}
