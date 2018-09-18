//
//  MockPokeGameDelegate.swift
//  PokeEngine_iOSTests
//
//  Created by Renaud Buisine on 04/09/2018.
//  Copyright © 2018 Renaud Buisine. All rights reserved.
//

import XCTest
@testable import PokeEngine_iOS

class MockPokeGameDelegate: NSObject {
    private var fixedUpdateExpectations: [XCTestExpectation]
    private var updateExpectations: [XCTestExpectation]
    private(set) var didFixedUpdateCalled: Bool
    private(set) var didUpdateCalled: Bool
    private(set) var addedScene: PokeScene?
    
    var expectations: [XCTestExpectation] {
        return fixedUpdateExpectations + updateExpectations;
    }
    
    override init() {
        fixedUpdateExpectations = []
        updateExpectations = []
        didFixedUpdateCalled = false
        didUpdateCalled = false
        addedScene = nil;
        
        super.init()
    }
    
    func addUpdateExpectations(_ count: Int) {
        MockPokeGameDelegate.addExpectations(in: &updateExpectations, count)
    }
    
    func addFixedUpdateExpectations(_ count: Int) {
        MockPokeGameDelegate.addExpectations(in: &fixedUpdateExpectations, count)
    }
    
    private static func addExpectations(in expectationsArray: inout [XCTestExpectation], _ count: Int) {
        for _ in 1...count {
            expectationsArray.append(XCTestExpectation(description: "MockPokeGameDelegate - Expectation"))
        }
    }
    
    func reset() {
        fixedUpdateExpectations = []
        updateExpectations = []
        didFixedUpdateCalled = false
        didUpdateCalled = false
    }
}

extension MockPokeGameDelegate: PokeGameDelegate {
    func game(_ game: PokeGame, didAdd scene: PokeScene) {
        addedScene = scene
    }
    
    func game(_ game: PokeGame, didUpdateWithElapsedTimestamp elapsedTimestamp: Float) {
        updateExpectations.popLast()?.fulfill()
        didUpdateCalled = true
    }
    
    func didFixedUpdate(_ game: PokeGame) {
        fixedUpdateExpectations.popLast()?.fulfill()
        didFixedUpdateCalled = true
    }
}
