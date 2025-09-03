#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Image comparison script using perceptual hash algorithm
Compare specific images with perceptual hash algorithm

Usage:
python compare_images.py image1.jpg image2.jpg
or
python compare_images.py
then follow prompts to input filenames
"""

import sys
import os
from perceptual_hash import ImageSimilarityAnalyzer


def compare_specific_images(image1_path, image2_path):
    """Compare two specified images"""
    print(f"=== Comparing Images: {image1_path} vs {image2_path} ===\n")
    
    # Check if files exist
    if not os.path.exists(image1_path):
        print(f"❌ Error: Image file {image1_path} does not exist")
        return
    
    if not os.path.exists(image2_path):
        print(f"❌ Error: Image file {image2_path} does not exist")
        return
    
    try:
        # Create analyzer
        analyzer = ImageSimilarityAnalyzer()
        
        # Compare images
        result = analyzer.compare_images(image1_path, image2_path)
        
        # Display results
        print("📊 Similarity Analysis Results:")
        print("-" * 50)
        
        similarities = []
        for hash_type, data in result['results'].items():
            similarity = data['similarity']
            similarities.append(similarity)
            print(f"{hash_type:>8}: {similarity:>6.2f}%")
        
        # Calculate average similarity
        avg_similarity = sum(similarities) / len(similarities)
        print("-" * 50)
        print(f"{'Average':>8}: {avg_similarity:>6.2f}%")
        
        # Similarity assessment
        print(f"\n🎯 Similarity Assessment:")
        if avg_similarity >= 90:
            print("   🔴 Highly Similar - Likely same image with different versions")
        elif avg_similarity >= 80:
            print("   🟠 Very Similar - Basically same content with minor differences")
        elif avg_similarity >= 60:
            print("   🟡 Moderately Similar - Some similarity but obvious differences")
        elif avg_similarity >= 40:
            print("   🟢 Low Similarity - Low similarity with significant differences")
        else:
            print("   🔵 Very Low Similarity - Almost completely different")
        
        # Ask if generate visualization
        print(f"\n📈 Generate visualization comparison? (y/n): ", end="")
        choice = input().strip().lower()
        
        if choice in ['y', 'yes', '是', '']:
            output_path = f"comparison_{os.path.splitext(os.path.basename(image1_path))[0]}_vs_{os.path.splitext(os.path.basename(image2_path))[0]}.png"
            analyzer.visualize_comparison(result, save_path=output_path)
            print(f"✅ Visualization saved to: {output_path}")
        
        return result
        
    except Exception as e:
        print(f"❌ Error during comparison: {e}")
        return None


def list_available_images():
    """List available image files in current directory"""
    image_extensions = ['.jpg', '.jpeg', '.png', '.bmp', '.tiff', '.gif']
    image_files = []
    
    for file in os.listdir('.'):
        if any(file.lower().endswith(ext) for ext in image_extensions):
            image_files.append(file)
    
    if image_files:
        print("📁 Image files in current directory:")
        for i, file in enumerate(image_files, 1):
            print(f"  {i}. {file}")
        print()
        return image_files
    else:
        print("❌ No image files found in current directory")
        return []


def interactive_mode():
    """Interactive mode"""
    print("🎯 Interactive Image Comparison Mode")
    print("=" * 50)
    
    # List available images
    image_files = list_available_images()
    if not image_files:
        return
    
    # Select first image
    print("Please select the first image:")
    for i, file in enumerate(image_files, 1):
        print(f"  {i}. {file}")
    
    while True:
        try:
            choice1 = int(input("Enter number (1-{}): ".format(len(image_files))))
            if 1 <= choice1 <= len(image_files):
                image1_path = image_files[choice1 - 1]
                break
            else:
                print("❌ Please enter a valid number")
        except ValueError:
            print("❌ Please enter a number")
    
    # Select second image
    print(f"\nFirst image selected: {image1_path}")
    print("Please select the second image:")
    
    remaining_files = [f for i, f in enumerate(image_files, 1) if i != choice1]
    for i, file in enumerate(remaining_files, 1):
        print(f"  {i}. {file}")
    
    while True:
        try:
            choice2 = int(input("Enter number (1-{}): ".format(len(remaining_files))))
            if 1 <= choice2 <= len(remaining_files):
                image2_path = remaining_files[choice2 - 1]
                break
            else:
                print("❌ Please enter a valid number")
        except ValueError:
            print("❌ Please enter a number")
    
    print(f"\nSecond image selected: {image2_path}")
    
    # Execute comparison
    compare_specific_images(image1_path, image2_path)


def main():
    """Main function"""
    print("🔍 Perceptual Hash Algorithm Image Comparison Tool")
    print("=" * 50)
    
    if len(sys.argv) == 3:
        # Command line argument mode
        image1_path = sys.argv[1]
        image2_path = sys.argv[2]
        compare_specific_images(image1_path, image2_path)
        
    elif len(sys.argv) == 1:
        # Interactive mode
        print("Usage:")
        print("1. Command line mode: python compare_images.py image1.jpg image2.jpg")
        print("2. Interactive mode: python compare_images.py")
        print()
        
        choice = input("Use interactive mode? (y/n): ").strip().lower()
        if choice in ['y', 'yes', '是', '']:
            interactive_mode()
        else:
            print("Please use command line mode: python compare_images.py image1.jpg image2.jpg")
    
    else:
        print("❌ Parameter error!")
        print("Usage: python compare_images.py [image1] [image2]")
        print("or: python compare_images.py (interactive mode)")


if __name__ == "__main__":
    main()
