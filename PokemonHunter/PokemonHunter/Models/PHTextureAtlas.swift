//
//  PHTextureAtlas.swift
//  PokemonHunter
//
//  Created by Renaud Buisine on 08/09/2018.
//  Copyright © 2018 Renaud Buisine. All rights reserved.
//

import SpriteKit

enum PHTextureOrientation: String {
    case front = "front"
    case back = "back"
    case profil = "profil"
}

class PHTextureAtlas {
    
    private let animations: [String:[SKTexture]]
    private let textures: [String:SKTexture]
    
    init?(named plistName:String) {
        
        guard let atlasDict = PHPropertyFileManager.dictionary(From: plistName) else {
            return nil
        }
        
        guard let textureDictionary = PHTextureAtlas.textureAtlasDictionary(from: atlasDict) else {
            return nil
        }
        textures = textureDictionary
        
        guard let animationsArray = PHTextureAtlas.animatonsArray(from: atlasDict) else {
            return nil
        }
        animations = animationsArray.reduce([:], { (result, pair) -> [String:[SKTexture]] in
            let (key, values) = pair

            var result = result
            PHTextureOrientation.allOrientations.forEach({ orientation in
                let animationKey = PHTextureAtlas.mappedkey(from: key, orientation: orientation)
                result[animationKey] = values.compactMap{
                    let fullFrameKey = PHTextureAtlas.mappedkey(from: $0, orientation: orientation)
                    return textureDictionary[fullFrameKey]
                }
            })
            return result
        })
    }
}

//MARK: - Animations Textures

extension PHTextureAtlas {
    func textures(forAnimationKey key:String, orientation: PHTextureOrientation) -> [SKTexture]? {
        return animations[PHTextureAtlas.mappedkey(from: key, orientation: orientation)]
    }
}

//MARK: - OrientationHelpers

extension PHTextureAtlas {
    private static func mappedkey(from baseKey:String, orientation: PHTextureOrientation) -> String {
        return mappedkey(from:baseKey, orientationString:orientation.rawValue)
    }
    private static func mappedkey(from baseKey:String, orientationString: String) -> String {
        return baseKey + orientationString
    }
}

//MARK: - Init Helpers

extension PHTextureAtlas {
    private static func textureAtlasDictionary(from atlasDict: [String:Any]) -> [String: SKTexture]? {
        guard let textureName = atlasDict["texture"] as? String,
            let textureImage = UIImage(named: textureName) else {
                return nil
        }
        guard let frames = atlasDict["frames"] as? [[String: String]] else {
            return nil
        }
        
        let texture = SKTexture(image: textureImage)
        return frames.reduce([:]) { (result, frameDict) -> [String: SKTexture] in
            guard let key = frameDict["id"] else {
                    return result
            }
            var result = result
            
            PHTextureOrientation.allOrientationRawStrings.forEach{
                if let frameString = frameDict["frame_" + $0] {
                    let key = mappedkey(from: key, orientationString: $0)
                    result[key] = SKTexture(rect: CGRectFromString(frameString), in: texture)
                }
            }
            return result
        }
    }
    
    private static func animatonsArray(from atlasDict: [String: Any]) -> [String: [String]]? {
        guard let animatonsArray = atlasDict["animations"] as? [[String:Any]] else {
            return nil
        }
        
        return animatonsArray.reduce([:], { (result, animationDict) -> [String: [String]] in
            guard let name = animationDict["name"] as? String,
                let frames = animationDict["frames"] as? [String] else {
                    return result
            }
            var result = result
            result[name] = frames
            return result
        })
    }
}

private extension PHTextureOrientation {
    static var allOrientationRawStrings: [String] {
        return allOrientations.map{ return $0.rawValue }
    }
    
    static var allOrientations: [PHTextureOrientation] {
        return  [PHTextureOrientation.front, PHTextureOrientation.back, PHTextureOrientation.profil]
    }
}
