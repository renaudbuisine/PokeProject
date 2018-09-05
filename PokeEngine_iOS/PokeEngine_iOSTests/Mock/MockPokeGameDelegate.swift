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
    
    var expectations: [XCTestExpectation] {
        return fixedUpdateExpectations + updateExpectations;
    }
    
    override init() {
        fixedUpdateExpectations = []
        updateExpectations = []
        didFixedUpdateCalled = false
        didUpdateCalled = false
        
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
    func didFixedUpdate() {
        fixedUpdateExpectations.popLast()?.fulfill()
        didFixedUpdateCalled = true
    }
    
    func didUpdate(withElapsedTimestamp elapsedTimestamp: Float) {
        updateExpectations.popLast()?.fulfill()
        didUpdateCalled = true
    }
}
