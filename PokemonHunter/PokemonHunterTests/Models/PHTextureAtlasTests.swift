//
//  PHTextureAtlasTests.swift
//  PokemonHunterTests
//
//  Created by Renaud Buisine on 08/09/2018.
//  Copyright © 2018 Renaud Buisine. All rights reserved.
//

import XCTest
import SpriteKit

@testable import PokemonHunter

class PHTextureAtlasTests: XCTestCase {
    
    func testCreation() {
        var plistFileName: String!
        var resultAtlas: PHTextureAtlas?
        var animationTextures: [SKTexture]?
        
        let expectedFrameRectString = "{{28,0},{14, 21}}"
        
        XCTContext.runActivity(named: "GIVEN a plist file, configuration for PHTextureAtlas, and ll valid resources around") { _ in
            plistFileName = "PlayerCharacter"
        }
        
        XCTContext.runActivity(named: "WHEN creating PHTextureAtlas from this plist") { _ in
            resultAtlas = PHTextureAtlas(named: plistFileName)
        }
        
        XCTContext.runActivity(named: "THEN atlas is created") { _ in
            XCTAssertNotNil(resultAtlas)
        }
        XCTContext.runActivity(named: "WHEN requesting textures forwalk animation / profil") { _ in
            animationTextures = resultAtlas?.textures(forAnimationKey: "walk", orientation: .profil)
        }
        
        XCTContext.runActivity(named: "THEN atlas is created") { _ in
            guard let animationTextures = animationTextures else {
                XCTFail("Expected results")
                return
            }
            
            XCTAssertEqual(animationTextures.count, 6, "Expected 6, got \(animationTextures.count)")
            
            let frameRect = CGRectFromString(expectedFrameRectString)
            XCTAssertEqual(animationTextures[0].textureRect(), frameRect, "Expected \(expectedFrameRectString), got \(animationTextures[0].textureRect())")
        }
    }
    
}
