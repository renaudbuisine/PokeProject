//
//  GameViewController.swift
//  PokemonHunter
//
//  Created by Renaud Buisine on 04/09/2018.
//  Copyright © 2018 Renaud Buisine. All rights reserved.
//

import UIKit
import SpriteKit
import GameplayKit

class PHViewController: UIViewController {
    //MARK: - INPECTABLE
    @IBInspectable private var sceneFileName: String?
    
    //MARK: - PUBLIC
    var skView: SKView? {
        return self.view as? SKView
    }
    
    private(set) var scene: GKScene?
    
    //MARK: - Life Cycle
    override func viewDidLoad() {
        super.viewDidLoad()
        
        guard let fileName = sceneFileName else {
            return
        }
        
        scene = GKScene(fileNamed: fileName)
        guard let scene = scene,
            let sceneNode = scene.rootNode as? SKScene else {
                return
        }
        
        guard let view = self.skView else {
            return
        }
        
        view.presentScene(sceneNode)
        view.ignoresSiblingOrder = true
        
        #if DEBUG
        view.showsFPS = true
        view.showsNodeCount = true
        #endif
    }
    
    override var prefersStatusBarHidden: Bool {
        return true
    }
}
